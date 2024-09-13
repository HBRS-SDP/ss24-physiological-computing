cmake_minimum_required(VERSION 3.29)
project(cli)

set(CMAKE_CXX_STANDARD 20)

# Add the library directory
add_subdirectory(${CMAKE_SOURCE_DIR}/../lib ${CMAKE_BINARY_DIR}/lib)

# Add your CLI executable
add_executable(cli main.cpp)

# Link against the hri_physio library
target_link_libraries(cli PRIVATE hri_physio)

# Include the library's header files
target_include_directories(cli PRIVATE ${CMAKE_SOURCE_DIR}/../lib/src)
target_link_libraries(cli PRIVATE lsl yaml-cpp)
target_include_directories(cli PRIVATE
        ${CMAKE_SOURCE_DIR}/../lib/external/liblsl/include
        ${CMAKE_SOURCE_DIR}/../lib/external/yaml-cpp/include
)
