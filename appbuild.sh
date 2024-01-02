#!/bin/bash

rm -rf paragon_back

git clone -b $BRANCH  $REPO
cd paragon_back
mkdir build
cd build
cmake ..
cd ..
cmake --build build
cd build
ctest
cd ../..