// Thin wrapper around the Emscripten module produced by wasm/build.sh.

export async function loadMethodius(moduleUrl) {
    const imported = await import(moduleUrl);
    const factory = imported.default;
    if (typeof factory !== "function") {
        throw new Error(
            "Methodius module has no default factory. Rebuild with wasm/build.sh."
        );
    }
    const module = await factory();
    return bindMethodius(module);
}

export function bindMethodius(module) {
    function call(name, returnType, argTypes, args) {
        return module.ccall(name, returnType, argTypes, args);
    }

    return {
        module,

        eval(code) {
            const status = call("mefodij_eval", "number", ["string"], [code]);
            return {
                ok: status === 0,
                status,
                output: call("mefodij_output", "string", [], []),
                result: call("mefodij_result", "string", [], []),
                error: call("mefodij_error", "string", [], []),
            };
        },

        writeFile(path, contents) {
            const status = call(
                "mefodij_write_file",
                "number",
                ["string", "string"],
                [path, contents]
            );
            if (status !== 0) {
                throw new Error("Could not write '" + path + "' (status " + status + ").");
            }
        },
    };
}
