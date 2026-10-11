#!/usr/bin/env bash
# Run the native API checks, then the WebAssembly core tests.
set -euo pipefail

root=$(cd "$(dirname "$0")/.." && pwd)
cd "$root"

mkdir -p build/wasm

native_sources=()
while IFS= read -r -d '' file; do
    native_sources+=("$file")
done < <(find src -type f -name '*.cpp' ! -name 'main.cpp' ! -name 'test.cpp' -print0)

g++ -std=c++17 -O2 -Iinclude \
    "${native_sources[@]}" wasm/api.cpp wasm/test/api_test.cpp \
    -o build/wasm/api_test

./build/wasm/api_test
echo "Native API checks passed."

./wasm/build.sh
node --test wasm/test/core.test.mjs
echo "WebAssembly core tests passed."
