#!/bin/bash

if [ -d "paragon_back" ]; then
    rm -rf paragon_back
fi

git clone -b $BRANCH $REPO paragon_back
cd paragon_back
cmake -Bbuild -GNinja
cmake --build build --target all
ctest --test-dir build
cd ..
