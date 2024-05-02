#include <expected>
#include <iostream>
#include <string_view>

struct Info {};
struct Msg {};

struct ExceptionBadClient : std::runtime_error {
  using std::runtime_error::runtime_error;
  Msg msg_;
};

using ExpectedProcessing = std::expected<Msg, ExceptionBadClient>;

bool send(const Msg&) { return true; }
bool send_error(const Msg&) { return true; }

ExpectedProcessing apply(const Info&) {
  return std::unexpected(ExceptionBadClient{"illegal format"});
}

bool process(const Info& data) {
  ExpectedProcessing result = apply(data);
  if (result.has_value()) return send(*result);
  std::cerr << "error : " << result.error().what() << std::endl;
  return send_error(result.error().msg_);
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
