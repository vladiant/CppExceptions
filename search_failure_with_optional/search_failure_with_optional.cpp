#include <cassert>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <source_location>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

struct Order {
  unsigned int id_;
  double value_;
};

std::ostream& operator<<(std::ostream& os, const Order& order) {
  os << "value : " << order.value_;
  return os;
}

std::map<unsigned int, Order> orders{{1, Order{1, 2.0}}, {11, Order{11, 5.0}}};

std::optional<Order> findOrder(unsigned int id) {
  auto it = orders.find(id);
  if (it == orders.end()) return std::nullopt;
  return it->second;
}

bool funcb(unsigned int id) {
  std::optional<Order> opt_ord =
      findOrder(id).or_else([] -> std::optional<Order> {
        std::cout << "Order not found";
        return std::nullopt;
      });
  return opt_ord.has_value();
}
bool funca(unsigned int id) {
  return findOrder(id)
      .or_else([] -> std::optional<Order> {
        std::cout << "Order not found";
        return std::nullopt;
      })
      .has_value();
}

int main() {
  try {
    funca(11);
    funcb(10);
  } catch (...) {
    std::cout << "Unknown exception" << std::endl;
  }
  std::cout << "End" << std::endl;
}
