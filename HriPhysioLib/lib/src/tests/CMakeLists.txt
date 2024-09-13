# Enable testing
enable_testing()

# Manually set the GoogleTest paths from Homebrew
include_directories(/opt/homebrew/opt/googletest/include)
link_directories(/opt/homebrew/opt/googletest/lib)

# Add the test executables
add_executable(test_ring_buffer test_ring_buffer.cpp)
target_link_libraries(test_ring_buffer gtest gtest_main pthread my_library)

add_executable(test_robot_manager test_robot_manager.cpp)
target_link_libraries(test_robot_manager gtest gtest_main pthread my_library)

# Register the tests with CTest
add_test(NAME RingBufferTest COMMAND test_ring_buffer)
add_test(NAME RobotManagerTest COMMAND test_robot_manager)