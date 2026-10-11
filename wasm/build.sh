#!/usr/bin/env bash
# Build the browser/Node module. Requires Emscripten (emcc) on PATH.
# Host filesystem, pthreads, locales, and the CLI main() are left out on purpose.
set -euo pipefail

root=$(cd "$(dirname "$0")/.." && pwd)
cd "$root"

if ! command -v em++ >/dev/null 2>&1; then
    echo "em++ was not found. Install the Emscripten SDK and source emsdk_env.sh." >&2
    echo "Steps are in wasm/README.md." >&2
    exit 1
fi

mkdir -p build/wasm

sources=()
while IFS= read -r -d '' file; do
    sources+=("$file")
done < <(find src -type f -name '*.cpp' ! -name 'main.cpp' ! -name 'test.cpp' -print0)

em++ "${sources[@]}" wasm/api.cpp \
    -Iinclude \
    -std=c++17 \
    -O2 \
    -fexceptions \
    -sDISABLE_EXCEPTION_CATCHING=0 \
    -sMODULARIZE=1 \
    -sEXPORT_ES6=1 \
    -sEXPORT_NAME=createMefodij \
    -sENVIRONMENT=web,webview,worker,node \
    -sALLOW_MEMORY_GROWTH=1 \
    -sSTACK_SIZE=1048576 \
    -sFILESYSTEM=1 \
    -sEXPORTED_FUNCTIONS='["_mefodij_eval","_mefodij_output","_mefodij_result","_mefodij_error","_mefodij_write_file"]' \
    -sEXPORTED_RUNTIME_METHODS='["ccall","UTF8ToString"]' \
    --no-entry \
    -o build/wasm/mefodij.js

echo "Wrote build/wasm/mefodij.js and build/wasm/mefodij.wasm"
