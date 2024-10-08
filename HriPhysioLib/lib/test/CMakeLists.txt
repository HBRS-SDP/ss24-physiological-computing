cmake_minimum_required(VERSION 3.28)
project(hri_physio_tests)

set(CMAKE_CXX_STANDARD 20)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Add your test executable
add_executable(hri_physio_tests hilbert_transform_test.cpp)

# Specify the path to your dynamic library
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    # For macOS
    set(HRI_PHYSIO_LIB_PATH "${CMAKE_SOURCE_DIR}/../build/libhri_physio.dylib")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    # For Linux (e.g., Ubuntu)
    set(HRI_PHYSIO_LIB_PATH "${CMAKE_SOURCE_DIR}/../build/libhri_physio.so")
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

# Link against the dynamic library and Google Test
target_link_libraries(hri_physio_tests PRIVATE 
    ${HRI_PHYSIO_LIB_PATH}
    gtest_main
)

# Include the library's header files
target_include_directories(hri_physio_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
)

# Enable testing
enable_testing()

# Add the test
add_test(NAME hri_physio_tests COMMAND hri_physio_tests)