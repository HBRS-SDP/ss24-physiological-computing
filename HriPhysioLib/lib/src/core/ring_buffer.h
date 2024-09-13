/* ================================================================================
 * Copyright: (C) 2021, SIRRL Social and Intelligent Robotics Research Laboratory, 
 *     University of Waterloo, All rights reserved.
 * 
 * Authors: 
 *     Austin Kothig <austin.kothig@uwaterloo.ca>
 * 
 * CopyPolicy: Released under the terms of the BSD 3-Clause License. 
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */

/* ================================================================================
 * Copyright: (C) 2024, Trushar Ghanekar,
 *     Hochschule Bonn-Rhein-Sieg (H-BRS), All rights reserved.
 * 
 * Author: 
 *     Trushar Ghanekar <trushar.ghanekar@smail.inf.h-brs.de>
 * 
 * CopyPolicy: Released under the terms of the MIT License.
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */

#ifndef HRI_PHYSIO_RING_BUFFER_H
#define HRI_PHYSIO_RING_BUFFER_H

#include <iostream>
#include <mutex>

/**
 * @class RingBuffer
 * @bried Template class for a thread-safe ring buffer.
 * @tparam T
 */
template <class T>
class RingBuffer
{
    /**
     * Unique pointer to the buffer array.
     */
    std::unique_ptr<T[]> buffer;

    /**
     * Total length of the buffer.
     */
    std::size_t buffer_length;

    /**
     * Index of the head of the buffer.
     */
    std::size_t buffer_head;

    /**
     * Index of the tail of the buffer.
     */
    std::size_t buffer_tail;

    /**
     * Current size of the buffer.
     */
    std::size_t buffer_size;

    /**
     * Mutex for thread safety.
     */
    std::mutex lock;

public:
    /**
     * Constructor to initialize the ring buffer with a given length.
     * @param length buffer length.
     */
    explicit RingBuffer(const std::size_t length = 0) : buffer_length(length),
                                                        buffer_head(0),
                                                        buffer_tail(0),
                                                        buffer_size(0)
    {
        buffer_init(length);
    }

    /**
     * Deconstructor to clean up the buffer.
     */
    ~RingBuffer()
    {
        buffer.reset();
    }

    /**
     * Enqueue a single item.
     * @param item item to enqueue.
     * @return true if successful, false otherwise.
     */
    bool enqueue(const T &item)
    {
        lock.lock();

        if (buffer_length == 0)
        {
            lock.unlock();
            return false;
        }

        if (full())
        {
            buffer_head = (buffer_head + 1) % buffer_length;
            --buffer_size;
        }

        buffer[buffer_tail] = item;
        buffer_tail = (buffer_tail + 1) % buffer_length;
        ++buffer_size;

        lock.unlock();
        return true;
    }

    /**
     * Enqueue multiple items into the buffer.
     * @param items items to enqueue.
     * @param length number of items to enqueue.
     * @return true if successful, false otherwise.
     */
    bool enqueue(const T *items, const std::size_t length)
    {
        lock.lock();

        if (length > buffer_length || buffer_length == 0)
        {
            lock.unlock();
            return false;
        }

        if (buffer_size + length >= buffer_length)
        {
            buffer_head = (buffer_head + length) % buffer_length;
            buffer_size -= length;
        }

        for (std::size_t idx = 0; idx < length; ++idx)
        {
            buffer[buffer_tail] = items[idx];
            buffer_tail = (buffer_tail + 1) % buffer_length;
            ++buffer_size;
        }

        lock.unlock();
        return true;
    }

    /**
     * Dequeue a single item from the buffer.
     * @param item item to dequeue.
     * @return true if successful, false otherwise.
     */
    bool dequeue(T &item)
    {
        lock.lock();

        if (buffer_length == 0)
        {
            lock.unlock();
            return false;
        }

        if (empty())
        {
            lock.unlock();
            return false;
        }

        item = buffer[buffer_head];
        buffer_head = (buffer_head + 1) % buffer_length;
        --buffer_size;

        lock.unlock();
        return true;
    }

    /**
     * Dequeue multiple items from the buffer with optional overlap.
     * @param items items to dequeue.
     * @param length number of items to dequeue.
     * @param overlap number of items to overlap.
     * @return true if successful, false otherwise.
     */
    bool dequeue(T *items, const std::size_t length, const std::size_t overlap = 0)
    {
        lock.lock();

        if (length > buffer_length || buffer_length == 0 || overlap > length)
        {
            lock.unlock();
            return false;
        }

        if (length > buffer_size)
        {
            lock.unlock();
            return false;
        }

        std::size_t keep = length - overlap;
        std::size_t buffer_pos = buffer_head;
        for (std::size_t idx = 0; idx < length; ++idx)
        {
            items[idx] = buffer[buffer_pos];
            buffer_pos = (buffer_pos + 1) % buffer_length;

            if (idx < keep)
            {
                buffer_head = (buffer_head + 1) % buffer_length;
                --buffer_size;
            }
        }

        lock.unlock();
        return true;
    }

    /**
     * Get the item at the front of the buffer without removing it.
     * @param item item to get.
     * @return true if successful, false otherwise.
     */
    bool front(T &item)
    {
        lock.lock();

        if (buffer_length == 0)
        {
            lock.unlock();
            return false;
        }

        if (empty())
        {
            lock.unlock();
            return false;
        }

        item = buffer[buffer_head];
        lock.unlock();
        return true;
    }

    /**
     * Get multiple items from the front of the buffer without removing them.
     * @param items items to get.
     * @param length number of items to get.
     * @return true if successful, false otherwise.
     */
    bool front(T *items, const std::size_t length)
    {
        lock.lock();
        if (length > buffer_length || buffer_length == 0)
        {
            lock.unlock();
            return false;
        }

        if (length > buffer_size)
        {
            lock.unlock();
            return false;
        }

        std::size_t temp_head = buffer_head;
        for (std::size_t idx = 0; idx < length; ++idx)
        {
            items[idx] = buffer[temp_head];
            temp_head = (temp_head + 1) % buffer_length;
        }

        lock.unlock();
        return true;
    }

    /**
     * Get a pointer to the buffer data.
     * @return pointer to the buffer data.
     */
    inline T *data()
    {
        return (buffer_length != 0) ? buffer.get() : 0;
    }

    /**
     * Get a const pointer to the buffer data.
     * @return const pointer to the buffer data.
     */
    inline const T *data() const
    {
        return (buffer_length != 0) ? buffer.get() : 0;
    }

    /**
     * Check if the buffer is empty.
     * @return true if empty, false otherwise.
     */
    bool empty()
    {
        return buffer_size == 0;
    }

    /**
     * Check if the buffer is full.
     * @return true if full, false otherwise.
     */
    bool full()
    {
        return buffer_size >= buffer_length;
    }

    /**
     * Get the current size of the buffer.
     * @return current size of the buffer.
     */
    std::size_t size()
    {
        return buffer_size;
    }

    /**
     * Get the total length of the buffer.
     * @return total length of the buffer.
     */
    [[nodiscard]] std::size_t length() const
    {
        return buffer_length;
    }

    /**
     * Resize the buffer to a new length.
     * @param length new length of the buffer.
     */
    void resize(const std::size_t length)
    {
        lock.lock();

        buffer_length = length;
        buffer_init(buffer_length);

        lock.unlock();
    }

    /**
     * Clear the buffer.
     */
    void clear()
    {
        lock.lock();

        T emptyVar;
        for (std::size_t idx = 0; idx < buffer_length; ++idx)
        {
            buffer[idx] = emptyVar;
        }

        buffer_size = 0;
        buffer_head = 0;
        buffer_tail = 0;

        lock.unlock();
    }

private:
    /**
     * Initialize the buffer with a given length.
     * @param length length of the buffer.
     */
    void buffer_init(std::size_t length)
    {
        buffer.reset(new T[length]);
    }
};

#endif // HRI_PHYSIO_RING_BUFFER_H
