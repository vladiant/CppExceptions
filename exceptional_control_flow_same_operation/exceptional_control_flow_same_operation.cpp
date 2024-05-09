#include <expected>
#include <iostream>
#include <source_location>
#include <string_view>

struct Info {};
struct Msg {};

struct ExceptionOrderNotFound : std::runtime_error {
  using std::runtime_error::runtime_error;
  Msg msg_;
};
struct ExceptionIllegalCurrency : std::runtime_error {
  using std::runtime_error::runtime_error;
  Msg msg_;
};
struct ExceptionInvalidClientId : std::runtime_error {
  using std::runtime_error::runtime_error;
  Msg msg_;
};

bool send(const Msg& request) {
  (void)request;
  return true;
}

Msg apply(const Info& data) {
  (void)data;
  throw ExceptionOrderNotFound{"illegal format"};
  return Msg{};
}

bool process(const Info& data) {
  try {
    Msg request = apply(data);
    return send(request);
  } catch (ExceptionOrderNotFound& e) {
    return send(e.msg_);
  } catch (ExceptionIllegalCurrency& e) {
    return send(e.msg_);
  } catch (ExceptionInvalidClientId& e) {
    return send(e.msg_);
  }
  return true;
}

int main() {
  try {
    process(Info{});
  } catch (...) {
    std::cout << "Unknown exception" << std::endl;
  }
  std::cout << "End" << std::endl;
  return 0;
}
