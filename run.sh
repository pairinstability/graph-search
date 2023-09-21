#!/bin/sh

set -e

if [ "$1" = "clean" ]; then
    rm -rf build bin out.dot out.png out.svg
    exit 0
fi


rm -rf build
mkdir build

cd build
CXX=/usr/bin/clang++ cmake -G Ninja ..
ninja

cd ..
#DEBUG=1 ./bin/testgraph
./bin/testgraph