#ifndef HRI_PHYSIO_MANAGER_THREAD_MANAGER_H
#define HRI_PHYSIO_MANAGER_THREAD_MANAGER_H

#include <atomic>
#include <functional>
#include <map>
#include <thread>
#include <vector>

class ThreadManager {
private:
    //-- A pool for threads, their running status, and the managers status.
    std::vector<std::thread> pool;
    std::map<std::thread::id, bool> status;
    std::atomic<bool> running;

    //-- Mutex for ensuring atomicity.
    std::mutex lock;

public:
    ThreadManager();

    virtual ~ThreadManager();

    std::thread::id add_thread(const std::function<void()> &func, bool start = true);

    std::thread::id add_loop_thread(const std::function<void(void)> &func, double period = 0.0, bool start = true);

    void interrupt_thread(std::thread::id thread_id);

    bool get_thread_status(std::thread::id thread_id);

    bool get_manager_running();

    void start();

    void stop();

    void close();

    void wait();

protected:
    virtual void sleep_thread(double seconds);

private:
    void set_thread_status(bool thread_status);

    void looper_wrapper(const std::function<void(void)> &func, double period);

public:
    //-- Disallow copy and assignment operators.
    ThreadManager(const ThreadManager &) = delete;

    ThreadManager &operator=(const ThreadManager &) = delete;
};

#endif /* HRI_PHYSIO_MANAGER_THREAD_MANAGER_H */
