# Specify the minimum version of CMake required.
cmake_minimum_required(VERSION 3.28)

# Define the project name.
project(hri_physio)

# Set the C++ standard to C++20.
set(CMAKE_CXX_STANDARD 20)

# Define the library target.
add_library(hri_physio SHARED


        # Utility source files.
        src/utilities/helpers.h

        # Processing
        src/processing/math.h
        src/utilities/helpers.h
)

# Explicitly set the linker language to C++.
# This is sometimes necessary for header-only libraries or when CMake can't determine the language automatically.
set_target_properties(hri_physio PROPERTIES LINKER_LANGUAGE CXX)
