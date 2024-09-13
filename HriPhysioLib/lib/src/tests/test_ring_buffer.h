#ifndef RING_BUFFER_TEST_H
#define RING_BUFFER_TEST_H
#include <gtest/gtest.h>
#include "core/ring_buffer.h"  // Adjust the path as per your project

// Test if the buffer initializes correctly
TEST(RingBufferTest, InitializeBuffer) {
    RingBuffer<int> buffer(10);  // Assuming the buffer takes a size as a constructor argument
    EXPECT_TRUE(buffer.isEmpty());
    EXPECT_EQ(buffer.size(), 0);
}

// Test if push and pop works as expected
TEST(RingBufferTest, PushAndPop) {
    RingBuffer<int> buffer(5);
    buffer.push(1);
    buffer.push(2);
    EXPECT_EQ(buffer.pop(), 1);
    EXPECT_EQ(buffer.pop(), 2);
}

// Test for overflow handling (if implemented)
TEST(RingBufferTest, OverflowHandling) {
    RingBuffer<int> buffer(2);
    buffer.push(1);
    buffer.push(2);
    buffer.push(3);  // Assume buffer overwrites old data
    EXPECT_EQ(buffer.pop(), 2);  // Oldest data should have been overwritten
}
#endif // RING_BUFFER_TEST_H
