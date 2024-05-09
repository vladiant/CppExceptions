#include <expected>
#include <iostream>
#include <source_location>
#include <string_view>

struct Info {};
struct Msg {};

struct ExceptionBadClient : std::runtime_error {
  using std::runtime_error::runtime_error;
  Msg msg_;
};

bool send(const Msg&) { return true; }
bool send_error(const Msg&) { return true; }

Msg apply(const Info&) {
  throw ExceptionBadClient{"illegal format"};
  return Msg{};
}

bool process(const Info& data) {
  try {
    Msg request = apply(data);
    return send(request);
  } catch (ExceptionBadClient& e) {
    return send_error(e.msg_);
  }
  return true;
}

int main() {
  try {
    process(Info{});
  } catch (ExceptionBadClient& e) {
    std::cout << " Order not found : " << e.what() << std::endl;
  } catch (...) {
    std::cout << "Unknown exception" << std::endl;
  }
  std::cout << "End" << std::endl;
  return 0;
}
