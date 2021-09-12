#pragma once
#include <fstream>
#include <string>

namespace lib::utils {
// Примечание:
// Reader читает файл полностью в оперативку, если файл большой,
// то необходимо разбивать его на части в зависимости от объема оперативной
// памяти.
class Reader {
public:
  Reader(const std::string &filename);

  void read();
  bool end() const;
  char get_next_symbol();

private:
  std::string filename_;
  std::ifstream file_;
  std::string buffer_;
  size_t carriage_{0};
};
} // namespace lib::utils
