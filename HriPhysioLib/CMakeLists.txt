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
        # Stream-related source files.
        src/stream/streamer_interface.cpp
        src/stream/streamer_interface.h
        src/stream/streamer_factory.cpp
        src/stream/streamer_factory.h
        src/stream/csv_streamer.cpp
        src/stream/csv_streamer.h
        src/stream/lsl_streamer.cpp
        src/stream/lsl_streamer.h

        # Utility source files.
        src/utilities/arg_parser.cpp
        src/utilities/arg_parser.h
        src/utilities/enums.h
        src/utilities/helpers.cpp
        src/utilities/helpers.h

        # Social interaction related source files.
        src/social/robot_interface.cpp
        src/social/robot_interface.h

        # Threading
        src/manager/thread_manager.h
        src/manager/thread_manager.cpp

        # Managers
        src/manager/robot_manager.cpp
        src/manager/robot_manager.h

        # Core
        src/core/ring_buffer.h

        # Processing
        src/processing/pocketfft.h
        src/processing/math.h
        src/processing/spectrogram.h
        src/processing/spectrogram.cpp
        src/processing/hilbert_transform.h
        src/processing/hilbert_transform.cpp
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