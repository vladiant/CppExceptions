#include <expected>
#include <iostream>
#include <string_view>

struct Info {};
struct Msg {};

template <typename DATA_T>
class OmegaException {
 public:
  OmegaException(const char* str, const DATA_T& data)
      : err_str(str), data_(data) {}
  OmegaException(std::string str, DATA_T& data)
      : err_str(std::move(str)), data_(std::move(data)) {}
  DATA_T& data() { return data_; }
  const DATA_T& data() const noexcept { return data_; }
  std::string& what() { return err_str; }
  const std::string& what() const noexcept { return err_str; }

 private:
  std::string err_str;
  DATA_T data_;
};

using ExceptionBadClient = OmegaException<Msg>;

using ExpectedProcessing = std::expected<Msg, ExceptionBadClient>;

bool send(const Msg&) { return true; }
bool send_error(const Msg&) { return true; }

ExpectedProcessing apply(const Info&) {
  return std::unexpected(ExceptionBadClient{"illegal format", Msg{}});
}

bool process(const Info& data) {
  ExpectedProcessing result = apply(data);
  if (result.has_value()) return send(*result);
  std::cerr << "error : " << result.error().what() << std::endl;
  return send_error(result.error().data());
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
