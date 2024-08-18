# Specify the minimum version of CMake required.
cmake_minimum_required(VERSION 3.28)

# Define the project name.
project(hri_physio)

# Set the C++ standard to C++20.
set(CMAKE_CXX_STANDARD 20)

# Define the library target.
add_library(hri_physio SHARED
        src/utilities/helpers.cpp
        src/utilities/helpers.h
        src/utilities/enums.h
        src/utilities/arg_parser.cpp
        src/utilities/arg_parser.h
        src/stream/streamer_interface.cpp
        src/stream/streamer_interface.h
        src/stream/csv_streamer.cpp
        src/stream/csv_streamer.h
)

# Explicitly set the linker language to C++.
# This is sometimes necessary for header-only libraries or when CMake can't determine the language automatically.
set_target_properties(hri_physio PROPERTIES LINKER_LANGUAGE CXX)