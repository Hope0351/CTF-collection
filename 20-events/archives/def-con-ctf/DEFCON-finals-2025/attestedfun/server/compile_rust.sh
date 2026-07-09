#!/bin/bash
set -euo pipefail

BIN_NAME="attestedfun"

# Ensure you're in project root
if [ ! -f Cargo.toml ]; then
    echo "Run this script from the project root (where Cargo.toml is)."
    exit 1
fi

#export RUSTFLAGS="-Z sanitizer=leak -C opt-level=3 -C target-feature=+sse,+sse2,+sse3,+ssse3,+sse4.1,+sse4.2,+avx,+avx2,+fma --C llvm-args=--inline-threshold=321" #2002
export RUSTFLAGS="-C opt-level=3 -C target-feature=+sse,+sse2,+sse3,+ssse3,+sse4.1,+sse4.2,+avx,+avx2,+fma --C llvm-args=--inline-threshold=1001" #2002
export CC=clang

# only clean if the first argument is "recompile"
if [ "${1:-}" = "recompile" ]; then
    echo "Recompile requested: running cargo clean..."
    cargo clean
fi

cargo build --release --bin "$BIN_NAME"

BIN="target/release/$BIN_NAME"
if [ ! -f "$BIN" ]; then
    echo "Error: $BIN not found!"
    exit 1
fi

strip --strip-all "$BIN"
echo "Sanitized and stripped binary at: $BIN"

cp "$BIN" .

echo "Done!"
