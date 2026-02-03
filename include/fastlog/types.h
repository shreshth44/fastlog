#pragma once

#include <cstdint>
#include <string>

namespace fastlog {

enum class LogLevel { INFO, WARN, ERROR, DEBUG, UNKNOWN };

struct LogEntry {
  uint64_t timestamp;
  LogLevel level;
  std::string message;
};

} // namespace fastlog
