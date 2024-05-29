#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

enum MyStatus { good, not_good, bad };

void check(const std::vector<int>& in) {
  if (in.empty()) throw not_good;
}

std::vector<int> apply(const std::vector<int> in) {
  if (in.size() < 3) throw bad;
  return in;
}

int main() {
  bool stay_active = true;
  auto v = std::vector<int>{{1, 2}};
  while (stay_active) {
    try {
      check(v);
      apply(v);
    } catch (const MyStatus& s) {
      std::cout << "error : " << s << std::endl;
    } catch (...) {
      std::cout << "Unknown Exception" << std::endl;
    }
    stay_active = false;
  }
}
