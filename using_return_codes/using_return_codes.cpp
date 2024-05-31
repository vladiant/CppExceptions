#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

enum MyStatus { good, not_good, bad };

MyStatus check(const std::vector<int>& in) {
  if (in.empty()) return not_good;
  return good;
}

MyStatus apply(std::vector<int> out) {
  if (out.size() < 3) return bad;
  return good;
}

int main() {
  auto v = std::vector<int>{{1, 2}};
  MyStatus rc = check(v);
  if (rc != good) {
    std::cout << "error : " << rc << std::endl;
    exit(-1);
  }
  rc = apply(v);
  if (rc != good) std::cout << "error : " << rc << std::endl;
}
