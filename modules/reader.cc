#include "reader.hh"
#include "logger.hh"

#include <sstream>

namespace lib::utils {

Reader::Reader(const std::string &filename)
    : filename_{filename}, file_{filename_} {
  LogInfo("Initialized reader with filename {}", filename);
}

void Reader::read() {
  if (!file_) {
    throw std::runtime_error{"Can't open file " + filename_ + ", check path"};
  }
  std::stringstream stream;
  stream << file_.rdbuf();
  buffer_ = stream.str();
}

bool Reader::end() const { return buffer_.size() <= carriage_; }
char Reader::get_next_symbol() { return buffer_[carriage_++]; }

} // namespace lib::utils
