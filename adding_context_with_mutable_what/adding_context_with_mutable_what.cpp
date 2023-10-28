#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

class MyException {
 public:
  MyException(std::string str) : err_str(std::move(str)) {}
  std::string& what() noexcept { return err_str; }
  const std::string& what() const noexcept { return err_str; }

 private:
  std::string err_str;
};

enum class component_type { text, graphic, heading };

std::string get_name_from_type(component_type) { return "name"; }

int transmit(std::string& name) {
  throw MyException(name + " is bad");
  return 1;
}

std::string format_addkey(int key, component_type type) {
  std::stringstream ss;
  ss << " key : " << key << ", type : " << static_cast<int>(type);
  return ss.str();
}

int funca(int key, component_type type) {
  try {
    auto name = get_name_from_type(type);
    return transmit(name);
  } catch (MyException& e) {
    std::stringstream ss;
    e.what() += format_addkey(key, type);
    throw;
  }
}

int main(int argc, char** argv) {
  try {
    if (funca(2, component_type::text)) std::cout << "success" << std::endl;
  } catch (const MyException& e) {
    std::cout << e.what() << std::endl;
  }
  /*
  catch(std::runtime_error& e) {
      std::cout << e.what() << std::endl;
  }
  */
  std::cout << "End" << std::endl;
}
