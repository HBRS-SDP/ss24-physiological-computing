# Specify the minimum version of CMake required.
cmake_minimum_required(VERSION 3.28)

# Define the project name.
project(hri_physio)

# Set the C++ standard to C++20.
set(CMAKE_CXX_STANDARD 20)

# Add submodules
add_subdirectory(external/liblsl)
add_subdirectory(external/yaml-cpp)

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
        src/stream/lsl_streamer.cpp
        src/stream/lsl_streamer.h
)

# Explicitly set the linker language to C++.
# This is sometimes necessary for header-only libraries or when CMake can't determine the language automatically.
set_target_properties(hri_physio PROPERTIES LINKER_LANGUAGE CXX)

# Link third-party packages and include directories
target_link_libraries(hri_physio PRIVATE lsl yaml-cpp)

target_include_directories(hri_physio PRIVATE
        ${CMAKE_SOURCE_DIR}/external/liblsl/include
        ${CMAKE_SOURCE_DIR}/external/yaml-cpp/include
)