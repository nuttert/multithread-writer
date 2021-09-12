#include "threads_manager.hh"
#include "logger.hh"

namespace lib::utils
{
  ThreadsManager::ThreadsManager(const size_t size, Callback &&callback)
      : size_{size}, callback_{callback}, cvs_(size)
  {
    if (!callback)
    {
      throw std::runtime_error{"Callback must be initialized"};
    }
    if (!size)
    {
      throw std::runtime_error{"Size must be positive"};
    }

    threads_.reserve(size_);
    for (size_t thread_num = 0; thread_num < size; ++thread_num)
    {
      auto thread = Thread{[this, thread_num]()
                           {
                             callback_wrapper(thread_num);
                             --size_;
                           }};
      thread.detach();
      threads_.push_back(std::move(thread));
    }
    LogInfo("Initialized threads_manager with size {}", size);
  }

  void ThreadsManager::start()
  {
    is_running_ = true;
    cvs_.front().notify_all();
  }
  void ThreadsManager::stop()
  {
    is_running_ = false;
    for (auto &cv : cvs_)
    {
      cv.notify_all();
    }
  }
  void ThreadsManager::exit()
  {
    is_running_ = false;
    need_exit_ = true;
    for (auto &cv : cvs_)
    {
      cv.notify_all();
    }
  }

  void ThreadsManager::prepare_next_thread()
  {
    current_thread_num_ = (current_thread_num_ + 1) % size_;
  }
  size_t ThreadsManager::next_thread(size_t thread_num) const
  {
    return (thread_num + 1) % size_;
  }

  void ThreadsManager::callback_wrapper(const size_t thread_num)
  {
    auto &cv = cvs_[thread_num];
    auto &next_cv_ = cvs_[next_thread(thread_num)];

    while (true)
    {
      std::unique_lock<Mutex> lock(mutex_);

      cv.wait(lock, [this, thread_num]
              { return need_exit_ || (is_running_ && current_thread_num_ == thread_num); });

      if (need_exit_)
      {
        return;
      }

      callback_();

      // Уловие 3:
      // "когда любой поток выводит символ на экран, для него устанавливается
      // "ограничение не вывод" и он временно не может выводить ничего более"
      prepare_next_thread();
      // Условие 4:
      // "когда любой поток выводит символ на экран, то со всех других потоков
      // снимается "ограничение на вывод" Примечание: Тем не менее из wait()
      // выйдет лишь один поток и напечатает следующий символ, в противном случае
      // порядок символов будет недетерминированным
      lock.unlock();
      next_cv_.notify_all();
      // cvs_[0].notify_one();
    }
  }

  void ThreadsManager::wait()
  {
    std::unique_lock<Mutex> lock(mutex_);
    for (auto &cv : cvs_)
    {
      cv.wait(lock, [this]
              { return !is_running_; });
    }
  }
} // namespace lib::utils
