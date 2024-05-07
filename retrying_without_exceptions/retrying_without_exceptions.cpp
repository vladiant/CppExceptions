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

std::ostream& operator<<(std::ostream& os,
                         const std::source_location& location) {
  os << "file: " << location.file_name() << "(" << location.line() << ":"
     << location.column() << ") `" << location.function_name();
  return os;
}

using MyExceptionVoid = MyException<void*>;

bool connect() {
  std::cout << "Trying to connect" << std::endl;
  // throw MyExceptionVoid("failed", nullptr);
  return false;
}
void notify(bool status) {
  if (status)
    std::cout << "Connection Succeeded" << std::endl;
  else
    std::cout << "Connection Failed" << std::endl;
}

bool try_connection(int max_retries) {
  bool connected = false;
  int retry_count = 0;
  while (!connected && (retry_count++ < max_retries)) {
    connected = connect();
    std::cout << "retry count : " << retry_count << std::endl;
  }
  notify(connected);
  return connected;
}

int main() {
  try {
    try_connection(3);
  } catch (MyExceptionVoid& e) {
    std::cout << e.where() << " Order not found : " << e.what() << std::endl;
  } catch (...) {
    std::cout << "Unknown exception" << std::endl;
  }
  std::cout << "End" << std::endl;
  return 0;
}
