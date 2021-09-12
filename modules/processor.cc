#include "processor.hh"
#include "config.hh"
#include "logger.hh"

#include <iostream>

namespace lib {
Processor::Processor()
    : threads_manager_(config::kThreadsNum, [this]() { write_next_symbol(); }),
      reader_(config::kFileName) {
  LogInfo("Initialized processor with file {} and threads num {}",
          config::kFileName, config::kThreadsNum);
}

// Условие 1:
// "родительский поток/процесс не может ничего выводить на экран"
// т.к. передаем коллбэк в дочерние потоки
// Условие 2:
// "за один раз один поток не может выводить более одного символа на экран"
void Processor::write_next_symbol() {
  if (reader_.end()) {
    stop();
    return;
  }
  const char next_symbol = reader_.get_next_symbol();
  std::cout << next_symbol;
}

void Processor::start() {
  reader_.read();
  threads_manager_.start();
}
void Processor::stop() { threads_manager_.stop(); }
void Processor::wait() { threads_manager_.wait(); }
void Processor::exit() { threads_manager_.exit(); }

} // namespace lib
