#ifndef HRI_PHYSIO_MANAGER_THREAD_MANAGER_H
#define HRI_PHYSIO_MANAGER_THREAD_MANAGER_H

#include <functional>
#include <map>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

/**
 * @class ThreadManager
 * @brief Manages a pool of threads, their running status, and the manager's status.
 */
class ThreadManager
{
    /**
     * A pool for threads.
     */
    std::vector<std::thread> pool;

    /**
     * Map to track the running status of each thread.
     */
    std::map<std::thread::id, bool> status;

    /**
     * Atomic flag to indicate if the manager is running.
     */
    std::atomic<bool> running;

    /**
     * Mutex for ensuring atomicity.
     */
    std::mutex lock;

public:
    /**
     * Constructor to initialize the ThreadManager.
     */
    ThreadManager();

    /**
     * Destructor to clean up resources.
     */
    virtual ~ThreadManager();

    /**
     * Adds a new thread to the pool.
     * @param func Function to be executed by the thread.
     * @param start Flag to indicate if the thread should start immediately.
     * @return ID of the newly added thread.
     */
    std::thread::id add_thread(const std::function<void()> &func, bool start = true);

    /**
     * Adds a new loop thread to the pool.
     * @param func Function to be executed by the thread.
     * @param period Time period between each loop iteration.
     * @param start Flag to indicate if the thread should start immediately.
     * @return ID of the newly added loop thread.
     */
    std::thread::id add_loop_thread(const std::function<void(void)> &func, double period = 0.0, bool start = true);

    /**
     * Interrupts a thread by its ID.
     * @param thread_id ID of the thread to be interrupted.
     */
    void interrupt_thread(std::thread::id thread_id);

    /**
     * Gets the running status of a thread.
     * @param thread_id ID of the thread.
     * @return True if the thread is running, false otherwise.
     */
    bool get_thread_status(std::thread::id thread_id);

    /**
     * Gets the running status of the manager.
     * @return True if the manager is running, false otherwise.
     */
    bool get_manager_running();

    /**
     * Starts the manager.
     */
    void start();

    /**
     * Stops the manager.
     */
    void stop();

    /**
     * Closes the manager and cleans up resources.
     */
    void close();

    /**
     * Waits for all threads to finish.
     */
    void wait();

protected:
    /**
     * Puts the current thread to sleep for a specified duration.
     * @param seconds Duration in seconds.
     */
    virtual void sleep_thread(double seconds);

private:
    /**
     * Sets the running status of a thread.
     * @param thread_status Status to be set.
     */
    void set_thread_status(bool thread_status);

    /**
     * Wrapper function for loop threads.
     * @param func Function to be executed by the thread.
     * @param period Time period between each loop iteration.
     */
    void looper_wrapper(const std::function<void(void)> &func, double period);

public:
    // Disallow copy and assignment operators.
    ThreadManager(const ThreadManager &) = delete;
    ThreadManager &operator=(const ThreadManager &) = delete;
};

#endif /* HRI_PHYSIO_MANAGER_THREAD_MANAGER_H */
