#!/usr/bin/env bash
# Script to build Spectral and run the testsuite in the GitHub CI
set -e -u -x -o pipefail

# Build Spectral
cmake -G "Ninja" -B build -DCMAKE_C_COMPILER=/usr/bin/clang-17 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-17
cmake --build build --target pallasSpec2ir
cd build

# Build Swift specification library
ninja BuildSwiftLib

# Run the testsuite
ninja makeLitVenv
ninja checkV