#include <expected>
#include <iostream>
#include <source_location>
#include <string_view>

enum class parse_error { invalid_char, overflow };

template <typename ENUMT>
class MyException {
 public:
  MyException(const char* str, const ENUMT& code)
      : err_str(str), err_code(code) {}
  ENUMT& code() { return err_code; }
  std::string& what() { return err_str; }
  const std::source_location& where() { return location_; }

 private:
  std::string err_str;
  const std::source_location location_ = std::source_location::current();
  ENUMT err_code;
};
bool connect() {
  std::cout << "Trying to connect" << std::endl;
  // throw std::runtime_error("failed");
  return false;
}
void notify(bool status) {
  if (status)
    std::cout << "Connection Succeeded" << std::endl;
  else
    std::cout << "Connection Failed" << std::endl;
}

bool try_connection() {
  bool connected = false;
  int retry_count = 0;
  while (!connected) {
    try {
      connect();
      notify(connected = true);
    } catch (const std::runtime_error&) {
      std::cout << "retry count : " << retry_count << std::endl;
      if (++retry_count > 2) {
        notify(connected);
        throw;
      }
    }
  }
  return connected;
}
int main() {
  try {
    try_connection();
  } catch (...) {
    std::cout << "Unknown exception" << std::endl;
  }
  std::cout << "End" << std::endl;
  return 0;
}
