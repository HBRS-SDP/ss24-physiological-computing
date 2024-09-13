#!/usr/bin/env bash

# This script automates the build process for the library, providing a convenient 
# way to handle repetitive tasks. Instead of manually typing out the commands 
# each time, we can simply run this script, which ensures consistency and 
# reduces the risk of errors during the build process.

# We create a separate 'build' directory to keep the project root clean and 
# organized. By running 'cmake' and 'make' inside this directory, all generated 
# files, such as object files, executables, and CMake cache files, are contained 
# within 'build', leaving the source tree unaffected. This approach also makes 
# it easier to manage out-of-source builds, allowing for quick cleanup or 
# rebuilding without interfering with the source code.
 
rm -rf build/
mkdir build
cd build || exit

cmake ..
make