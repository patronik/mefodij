# Methodius in the browser

The WebAssembly build runs the interpreter inside a page or under Node. `друк` comes back as a string. `імпорт` reads files from an in-memory filesystem that you fill yourself. The command-line program (`-f`, `-r`) is a separate native build.

## Turned off in this build

These host features are not part of the browser module:

| Feature | What happens instead |
| --- | --- |
| `setlocale` and `locale("en_US.UTF-8")` | Source and files are decoded as UTF-8 in the interpreter. The browser has no `en_US.UTF-8` locale. |
| Wide console (`wcout`) | `друк` is appended to a buffer and returned by `mefodij_output()`. |
| Host filesystem | `імпорт` sees only files written with `mefodij_write_file()`. A file on disk is invisible. |
| CLI `main` (`-f`, `-r`) | Not linked. Call `mefodij_eval`. |
| Threads | Not enabled. The C API is not reentrant. |
| Google Test | Not linked. Core checks live in `wasm/test/`. |

`std::wregex` (the `~` operator) and C++ exceptions stay on. Exceptions are caught at the C boundary, so a Methodius error does not tear down the page.

## Install Emscripten

The build needs the Emscripten SDK (3.1.50 or newer, including 4.x).

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

Open a new shell with `source /path/to/emsdk/emsdk_env.sh` before building. `em++` has to be on `PATH`. The script uses `em++` rather than `emcc` so libc++ is linked.

## Compile

From the repository root:

```bash
./wasm/build.sh
```

The script compiles every `src/**/*.cpp` file except `main.cpp` and `test.cpp`, plus `wasm/api.cpp`. It writes:

- `build/wasm/mefodij.js`
- `build/wasm/mefodij.wasm`

Useful flags already set by the script:

- `-fexceptions` and `-sDISABLE_EXCEPTION_CATCHING=0` so `try/catch` inside the interpreter works
- `-sALLOW_MEMORY_GROWTH=1` so longer programs can allocate
- `-sSTACK_SIZE=1048576` (1 MiB) for nested calls
- `-sENVIRONMENT=web,webview,worker,node` so the same module loads in a page and in Node
- `--no-entry` because there is no `main`

Do not add `-sNODERAWFS`, `-pthread`, or a native locale package. Those put host behavior back.

## Test

```bash
./wasm/test.sh
```

That command does two things:

1. Builds `build/wasm/api_test` with the system `g++` and checks the C API, including UTF-8, captured `друк`, errors, and `імпорт` through `mefodij_write_file`.
2. Runs `wasm/build.sh`, then `node --test wasm/test/core.test.mjs` against the real `.wasm` module. Those tests also check that a file created on the Node disk is not visible to `імпорт`.

Node 20 or newer is required for the second step.

## Call it from JavaScript

`wasm/mefodij.js` wraps the exported functions. `moduleUrl` must point at `build/wasm/mefodij.js`, and `mefodij.wasm` must sit next to that file.

```javascript
import { loadMethodius } from "./wasm/mefodij.js";

const methodius = await loadMethodius(new URL("./build/wasm/mefodij.js", import.meta.url).href);

methodius.writeFile("функції.txt", `
функція додати(а, б) {
    вихід а + б;
}
`);

const evaluation = methodius.eval(`
імпорт "функції.txt";
друк додати(20, 22);
`);

evaluation.ok;      // true
evaluation.output;  // "42"  — everything passed to друк
evaluation.result;  // "42"  — value of the last expression
evaluation.error;   // ""    — set when ok is false
evaluation.status;  // 0 success, 1 Methodius error, 2 missing code
```

Each `eval` starts a new program. Variables and functions from the previous call are gone. Files written with `writeFile` stay until the page reloads.

Low-level exports, if you call `ccall` yourself:

| Export | Role |
| --- | --- |
| `mefodij_eval(code)` | Run UTF-8 source. Returns 0, 1, or 2. |
| `mefodij_output()` | UTF-8 text from `друк`. Valid until the next call. |
| `mefodij_result()` | UTF-8 text of the last value. |
| `mefodij_error()` | Empty after success. |
| `mefodij_write_file(path, contents)` | Create a virtual file. Returns 0, 1, or 2. |

Returned pointers are owned by the module. Copy them (the wrapper does) before the next call.

## Open the example page

ES modules cannot be loaded from `file://`. From the repository root, after `./wasm/build.sh`:

```bash
node wasm/serve.mjs
```

Then open `http://127.0.0.1:8080/wasm/example/`. The page loads the module, runs the sample, and shows `друк` output. The server sends `.wasm` as `application/wasm`.

A production page only needs `mefodij.js`, `mefodij.wasm`, and your own script that imports `loadMethodius`. Serve those files from the same origin.
