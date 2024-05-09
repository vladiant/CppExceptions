#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

class MyException {
 public:
  MyException(std::string str) : err_str(std::move(str)) {}
  std::string& what() noexcept { return err_str; }
  const std::string& what() const noexcept { return err_str; }

 private:
  std::string err_str;
};

class Request {};
class Response {};
class Service {
 public:
  Response send(const Request&) { return Response{}; }
};

std::ostream& operator<<(std::ostream& os, const Response&) { return os; }

Service service;
enum class response_error { success, bad_clientid, bad_order_id };

// if invalid return error
response_error check_bad_response(const Response&) {
  return response_error::bad_clientid;
}

Response make_error_response(const Response& resp) { return resp; }

Response execute(const Request& req) {
  auto resp = service.send(req);
  if (response_error rc = check_bad_response(resp);
      rc != response_error::success) {
    std::cerr
        << "Bad response : "
        << static_cast<typename std::underlying_type<response_error>::type>(rc)
        << " -> " << resp << std::endl;
    return make_error_response(resp);
  }

  return resp;
}

int main() {
  try {
    execute(Request{});
  } catch (...) {
    std::cout << "Unknown exception" << std::endl;
  }
  std::cout << "End" << std::endl;
}
