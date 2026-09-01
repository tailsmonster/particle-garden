#!/usr/bin/env bash
set -e

BUILD_DIR="build"

if [[ "$1" == "--clean" ]]; then
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

cmake -S . -B "$BUILD_DIR" -G Ninja
cmake --build "$BUILD_DIR"