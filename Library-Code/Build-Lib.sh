#!/bin/bash
set -e

rm -r build

BUILD_DIR=build
TOOLCHAIN_FILE=$1

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

if [[ -z "$TOOLCHAIN_FILE" ]]; then
    echo "Running native build..."
    cmake ..
else
    if [[ ! -f "../$TOOLCHAIN_FILE" ]]; then
        echo "Error: Toolchain file '../$TOOLCHAIN_FILE' not found!"
        exit 1
    fi
    echo "Cross-compiling with toolchain file: $TOOLCHAIN_FILE"
    cmake .. -DCMAKE_TOOLCHAIN_FILE="../$TOOLCHAIN_FILE"
fi

make

echo "✅ Build finished."
