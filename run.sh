#!/bin/sh

set -e

rm -rf build
mkdir build

cd build
CXX=/usr/bin/clang++ cmake -G Ninja ..
ninja

cd ..
./bin/testgraph