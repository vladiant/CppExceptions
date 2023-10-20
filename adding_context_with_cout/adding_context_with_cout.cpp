#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

enum class component_type { text, graphic, heading };

std::string get_name_from_type(component_type) { return "name"; }

int transmit(std::string& name) {
  throw std::runtime_error(name + " is bad");
  return 1;
}

int funca(int key, component_type type) {
  try {
    auto name = get_name_from_type(type);
    return transmit(name);
  } catch (std::runtime_error& e) {
    std::cout << "key : " << key << ", type : " << static_cast<int>(type)
              << " - " << e.what() << std::endl;
    throw;
  }
}

int main(int argc, char** argv) {
  try {
    if (funca(2, component_type::text)) std::cout << "success" << std::endl;
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
  /*
  catch(std::runtime_error& e) {
      std::cout << e.what() << std::endl;
  }
  */
  std::cout << "End" << std::endl;
}
