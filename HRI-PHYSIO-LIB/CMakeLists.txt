cmake_minimum_required(VERSION 3.28)
project(hri_physio)

set(CMAKE_CXX_STANDARD 26)

add_library(hri_physio SHARED
        src/stream/streamer_interface.cpp
        src/stream/streamer_interface.h
        src/utilities/enums.h
        src/utilities/helpers.cpp
        src/utilities/helpers.h
)
set_target_properties(hri_physio PROPERTIES LINKER_LANGUAGE CXX)