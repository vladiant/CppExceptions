#include <cassert>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <source_location>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

template <typename ENUMT>
class MyException {
 public:
  MyException(const char* str, const ENUMT& code)
      : err_str(str), err_code(code) {}
  ENUMT& code() { return err_code; }
  std::string& what() { return err_str; }

 private:
  std::string err_str;
  ENUMT err_code;
};

using MyExceptionErrsVoid = MyException<void*>;

struct Order {
  unsigned int id_;
  double value_;
};

std::ostream& operator<<(std::ostream& os, const Order& order) {
  os << "value : " << order.value_;
  return os;
}

std::map<unsigned int, Order> orders{{1, Order{1, 2.0}}, {11, Order{11, 5.0}}};

Order UpdateOrder(const Order& ord) {
  auto it = orders.find(ord.id_);
  if (it == orders.end()) throw MyExceptionErrsVoid("update error : ", nullptr);
  return it->second = ord;
}

Order findOrder(unsigned int id) {
  auto it = orders.find(id);
  if (it == orders.end()) throw MyExceptionErrsVoid("Order not found", nullptr);
  return it->second;
}

bool funca(unsigned int id) {
  try {
    Order ord = findOrder(id);
    std::cout << "Found order id : " << id << " : " << ord << std::endl;
    return true;
  } catch (MyExceptionErrsVoid& e) {
    std::cout << "Order not found : " << e.what() << std::endl;
  }
  return false;
}

int main() {
  try {
    unsigned int id = 10;
    if (funca(id) == 1) std::cout << "success" << std::endl;
  } catch (...) {
    std::cout << "Unknown exception" << std::endl;
  }
  std::cout << "End" << std::endl;
}
