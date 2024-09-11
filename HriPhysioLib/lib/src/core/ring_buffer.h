#ifndef HRI_PHYSIO_RING_BUFFER_H
#define HRI_PHYSIO_RING_BUFFER_H

#include <iostream>
#include <mutex>

template<class T>
class RingBuffer {
    std::unique_ptr<T[]> buffer;

    std::size_t buffer_length;
    std::size_t buffer_head;
    std::size_t buffer_tail;
    std::size_t buffer_size;

    std::mutex lock;

public:
    explicit RingBuffer(const std::size_t length = 0) : buffer_length(length),
                                                        buffer_head(0),
                                                        buffer_tail(0),
                                                        buffer_size(0) {
        buffer_init(length);
    }

    ~RingBuffer() {
        buffer.reset();
    }

    bool enqueue(const T &item) {
        lock.lock();

        if (buffer_length == 0) {
            lock.unlock();
            return false;
        }

        if (full()) {
            buffer_head = (buffer_head + 1) % buffer_length;
            --buffer_size;
        }

        buffer[buffer_tail] = item;
        buffer_tail = (buffer_tail + 1) % buffer_length;
        ++buffer_size;

        lock.unlock();
        return true;
    }

    bool enqueue(const T *items, const std::size_t length) {
        lock.lock();

        if (length > buffer_length || buffer_length == 0) {
            lock.unlock();
            return false;
        }

        if (buffer_size + length >= buffer_length) {
            buffer_head = (buffer_head + length) % buffer_length;
            buffer_size -= length;
        }

        for (std::size_t idx = 0; idx < length; ++idx) {
            buffer[buffer_tail] = items[idx];
            buffer_tail = (buffer_tail + 1) % buffer_length;
            ++buffer_size;
        }

        lock.unlock();
        return true;
    }

    bool dequeue(T &item) {
        lock.lock();

        if (buffer_length == 0) {
            lock.unlock();
            return false;
        }

        if (empty()) {
            lock.unlock();
            return false;
        }

        item = buffer[buffer_head];

        buffer_head = (buffer_head + 1) % buffer_length;
        --buffer_size;

        lock.unlock();
        return true;
    }

    bool dequeue(T *items, const std::size_t length, const std::size_t overlap = 0) {
        lock.lock();

        if (length > buffer_length || buffer_length == 0 || overlap > length) {
            lock.unlock();
            return false;
        }


        if (length > buffer_size) {
            lock.unlock();
            return false;
        }


        std::size_t keep = length - overlap;
        std::size_t buffer_pos = buffer_head;
        for (std::size_t idx = 0; idx < length; ++idx) {
            items[idx] = buffer[buffer_pos];
            buffer_pos = (buffer_pos + 1) % buffer_length;

            if (idx < keep) {
                buffer_head = (buffer_head + 1) % buffer_length;
                --buffer_size;
            }
        }

        lock.unlock();
        return true;
    }

    bool front(T &item) {
        lock.lock();

        if (buffer_length == 0) {
            lock.unlock();
            return false;
        }

        if (empty()) {
            lock.unlock();
            return false;
        }

        item = buffer[buffer_head];
        lock.unlock();
        return true;
    }

    bool front(T *items, const std::size_t length) {
        lock.lock();
        if (length > buffer_length || buffer_length == 0) {
            lock.unlock();
            return false;
        }

        if (length > buffer_size) {
            lock.unlock();
            return false;
        }

        std::size_t temp_head = buffer_head;
        for (std::size_t idx = 0; idx < length; ++idx) {
            items[idx] = buffer[temp_head];
            temp_head = (temp_head + 1) % buffer_length;
        }

        lock.unlock();
        return true;
    }

    inline T *data() {
        return (buffer_length != 0) ? buffer.get() : 0;
    }

    inline const T *data() const {
        return (buffer_length != 0) ? buffer.get() : 0;
    }

    [[nodiscard]] bool empty() const {
        return buffer_size == 0;
    }

    [[nodiscard]] bool full() const {
        return buffer_size >= buffer_length;
    }

    [[nodiscard]] std::size_t size() const {
        return buffer_size;
    }

    [[nodiscard]] std::size_t length() const {
        return buffer_length;
    }

    void resize(const std::size_t length) {
        lock.lock();

        buffer_length = length;
        buffer_init(buffer_length);

        lock.unlock();
    }

    void clear() {
        lock.lock();

        T emptyVar;
        for (std::size_t idx = 0; idx < buffer_length; ++idx) {
            buffer[idx] = emptyVar;
        }

        buffer_size = 0;
        buffer_head = 0;
        buffer_tail = 0;

        lock.unlock();
    }

private:
    void buffer_init(std::size_t length) {
        buffer.reset(new T[length]);
    }
};

#endif
