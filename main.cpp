#include "modules/config.hh"
#include "modules/logger.hh"
#include "modules/processor.hh"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void config_logger() {
  using namespace spdlog;

  using Seconds = std::chrono ::seconds;
  using ConsoleSink = ::spdlog::sinks::stdout_color_sink_mt;
  using FileSink = ::spdlog::sinks::basic_file_sink_mt;

  using Sinks = ::spdlog::sinks_init_list;

  spdlog::flush_every(Seconds(lib::config::kLoggerFlushSec));

  auto file_sink = std::make_shared<FileSink>(lib::config::kLogsPath);
  file_sink->set_level(::spdlog::level::trace);
  file_sink->set_pattern(lib::config::kLoggerPattern);

  auto logger = std::make_shared<::spdlog::logger>("test", Sinks({file_sink}));
  logger->set_level(::spdlog::level::trace);

  ::spdlog::set_default_logger(logger);
}

int main() {
  config_logger();
  lib::Processor processor{};
  processor.start();
  processor.wait();
  processor.exit();
  return 0;
}