#include <expected>
#include <iostream>
#include <source_location>
#include <variant>

template <typename... Ts>
struct Overloaded : Ts... {
  using Ts::operator()...;
};
template <typename... Ts>
Overloaded(Ts&&...) -> Overloaded<std::decay_t<Ts>...>;

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

using ExceptionProcessing =
    std::variant<ExceptionOrderNotFound, ExceptionIllegalCurrency,
                 ExceptionInvalidClientId>;
using ExpectedProcessing = std::expected<Msg, ExceptionProcessing>;

bool send(const Msg& request) {
  (void)request;
  return true;
}
bool send_error(const Msg&) { return true; }
bool send_warning(const Msg&) { return true; }
bool handle_bad_client(const Msg&) { return true; }

ExpectedProcessing apply(const Info& data) {
  (void)data;
  // return ExceptionOrderNotFound{"illegal format"};
  return Msg{};
}

bool process(const Info& data) {
  ExpectedProcessing result = apply(data);
  if (result.has_value()) return send(*result);
  auto visitor = Overloaded{
      [&](ExceptionIllegalCurrency& ex) { return send_error(ex.msg_); },
      [&](ExceptionOrderNotFound& ex) { return send_warning(ex.msg_); },
      [&](ExceptionInvalidClientId& ex) { return handle_bad_client(ex.msg_); }};
  return std::visit(visitor, result.error());
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
