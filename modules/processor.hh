#pragma once
#include "reader.hh"
#include "threads_manager.hh"

namespace lib {

class Processor {
public:
  Processor();

  void start();
  void stop();
  void exit();
  void wait();

private:
  void write_next_symbol();

private:
  utils::ThreadsManager threads_manager_;
  utils::Reader reader_;
};
} // namespace lib
