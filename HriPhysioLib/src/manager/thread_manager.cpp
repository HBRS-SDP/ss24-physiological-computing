#include "thread_manager.h"

ThreadManager::ThreadManager() {
    //-- Ensure we've empty control containers.
    pool.clear();
    status.clear();

    //-- Set the state of running.
    running = true;
}

ThreadManager::~ThreadManager() {
    //-- Close everything up.
    this->close();
}

std::thread::id ThreadManager::add_thread(const std::function<void()> &func, bool start) {
    //-- Lock the mutex to ensure read/write atomicity.
    lock.lock();

    //-- Spawn a thread with the provided function.
    pool.emplace_back(func); // Constructs std::thread directly in place

    //-- Get this threads id, and set it's state to the input boolean.
    std::thread::id thread_id = pool[pool.size() - 1].get_id();
    status[thread_id] = start;

    //-- Unlock the mutex and return.
    lock.unlock();

    //-- Return the thread id to the caller.
    return thread_id;
}

std::thread::id ThreadManager::add_loop_thread(const std::function<void()> &func, double period, bool start) {
    //-- Lock the mutex to ensure read/write atomicity.
    lock.lock();

    //-- Spawn a thread with the looper wrapper, taking the provided function and the looping period.
    pool.emplace_back(&ThreadManager::looper_wrapper, this, func, period);


    //-- Get this threads id, and set it's state to the input boolean.
    std::thread::id thread_id = pool[pool.size() - 1].get_id();
    status[thread_id] = start;

    //-- Unlock the mutex and return.
    lock.unlock();

    //-- Return the thread id to the caller.
    return thread_id;
}

void ThreadManager::interrupt_thread(std::thread::id thread_id) {
    //-- Lock the mutex to ensure read/write atomicity.
    lock.lock();

    //-- Try interrupting this thread.
    status[thread_id] = false;

    //-- Unlock the mutex and return.
    lock.unlock();
}

bool ThreadManager::get_thread_status(std::thread::id thread_id) {
    //TODO: Maybe don't lock here.. just return the status.

    //-- Lock the mutex to ensure read/write atomicity.
    lock.lock();

    //-- Get the status of this thread.
    bool thread_status = status[thread_id];

    //-- Unlock the mutex and return.
    lock.unlock();

    return thread_status;
}

bool ThreadManager::get_manager_running() {
    return running;
}

void ThreadManager::start() {
    if (this->get_manager_running()) {
        this->set_thread_status(true);
    }
}

void ThreadManager::stop() {
    this->set_thread_status(false);
}

void ThreadManager::close() {
    //-- Stop all the threads.
    this->stop();

    //-- Tell the threads to stop running.
    this->running = false;

    //-- Join all the threads.
    for (auto &idx: pool) {
        idx.join();
    }

    //-- Destroy all elements in the pool and running.
    pool.clear();
    status.clear();
}

void ThreadManager::wait() {
    //-- Wait for the thread manager to stop.
    while (this->get_manager_running()) {
        this->sleep_thread(0.5);
    }
}

void ThreadManager::sleep_thread(double seconds) {
    std::this_thread::sleep_for(
        std::chrono::duration<double>(seconds)
    );
}

void ThreadManager::set_thread_status(bool thread_status) {
    //-- Lock the mutex to ensure read/write atomicity.
    lock.lock();

    //-- Get an iterator to the start of the map.
    auto it = status.begin();
    while (it != status.end()) {
        it->second = thread_status;
        ++it;
    }

    //-- Unlock the mutex and return.
    lock.unlock();
}

void ThreadManager::looper_wrapper(const std::function<void()> &func, double period) {
    //-- Get the id for the current thread.
    const std::thread::id thread_id = std::this_thread::get_id();

    //-- Loop until it's time to shutdown.
    while (this->get_manager_running()) {
        //-- Get the clock time for now.
        auto start = std::chrono::system_clock::now();

        //-- Call the provided function if this thread is enabled.
        if (this->get_thread_status(thread_id)) {
            func();
        }

        //-- Sleep the thread for the remaining time of the period.
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> dur = end - start;
        double diff = period - dur.count();

        diff = (diff > 0.0) ? diff : 0.0;

        this->sleep_thread(diff);

        //auto loop_time = std::chrono::system_clock::now();
        //std::chrono::duration<double> loop_dur = loop_time - start;
        //std::cout << "[DEBUG] Thread id ("<< thread_id << ") executed in " << loop_dur.count() << " seconds." << std::endl;
    }
}


