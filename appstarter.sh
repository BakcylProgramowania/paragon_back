#!/bin/bash

rm -rf paragon_back

git clone https://github.com/BakcylProgramowania/paragon_back.git
cd paragon_back
mkdir build
cd build
cmake ..
cd ..
cmake --build build
cd ..
./paragon_back/build/src/example-main
