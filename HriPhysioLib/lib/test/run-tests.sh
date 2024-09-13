#!/usr/bin/env bash

rm -rf build/
mkdir build
cd build || exit

cmake ..
make

cd ..
./build/hri_physio_tests