#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

namespace lib::utils
{
  class ThreadsManager
  {
    using Thread = std::thread;
    using Mutex = std::mutex;
    using ConditionVariable = std::condition_variable;

  public:
    using Callback = std::function<void()>;

  public:
    ThreadsManager(const size_t size, Callback &&callback);
    ~ThreadsManager() { stop(); }

    void start();
    void stop();
    void exit();
    void wait();

    bool is_running() const { return is_running_; }
    size_t size() const { return size_; }

  private:
    void prepare_next_thread();
    size_t next_thread(size_t thread_num) const;
    void callback_wrapper(const size_t thread_num);

  private:
    size_t size_;
    Callback callback_;
    // Условие 5:
    // "когда выведен на экран первый символ, ни один новый поток не может быть
    // запущен" Примечание: Все потоки создаются вначале и содержатся в данном
    // контейнере
    std::vector<Thread> threads_;

    mutable Mutex mutex_;
    std::vector<ConditionVariable> cvs_;
    size_t current_thread_num_{0};

    bool is_running_{false};
    bool need_exit_{false};
  };
} // namespace lib::utils
