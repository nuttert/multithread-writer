#pragma once
#include "spdlog/spdlog.h"
#include <fmt/format.h>

#define LogInfo(...)                                                           \
  {                                                                            \
    spdlog::info("[path {}::{}()#{} {}] ", __FILE__, __FUNCTION__, __LINE__,   \
                 fmt::format(__VA_ARGS__));                                    \
  }
#define LogDebug(...)                                                          \
  {                                                                            \
    spdlog::info("[path {}::{}()#{} {}] ", __FILE__, __FUNCTION__, __LINE__,   \
                 fmt::format(__VA_ARGS__));                                    \
  }

#define LogError(...)                                                          \
  {                                                                            \
    spdlog::error("[path {}::{}()#{} {}] ", __FILE__, __FUNCTION__, __LINE__,  \
                  fmt::format(__VA_ARGS__));                                   \
  }
#define LogWarning(...)                                                        \
  {                                                                            \
    spdlog::warn("[path {}::{}()#{} {}] ", __FILE__, __FUNCTION__, __LINE__,   \
                 fmt::format(__VA_ARGS__));                                    \
  }
