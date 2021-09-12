#pragma once
#include <cstddef>

namespace lib::config {
// Threads Manager
constexpr size_t kThreadsNum = 4;

// Reader
constexpr char kFileName[14] = "ascii-art.txt";

// Logger
constexpr char kLogsPath[11] = "./logs.log";
constexpr size_t kLoggerFlushSec = 1;
constexpr char kLoggerPattern[52] =
    "[time %H:%M:%S--%D %z] [type %^%l%$] [thread %t] %v";
} // namespace lib::config
