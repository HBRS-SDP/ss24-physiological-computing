cmake_minimum_required(VERSION 3.28)
project(HRIPHY)

set(CMAKE_CXX_STANDARD 23)

add_library(hri_physio SHARED library.cpp
        src/helpers.h
        src/Core/graph.cpp
        src/Core/graph.h
        src/Core/ringBuffer.h
        src/Social/robotInterface.cpp
        src/Social/robotInterface.h
        src/Manager/threadManager.cpp
        src/Manager/threadManager.h
)