#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

enum class component_type { text, graphic, heading };

class MyException {
 public:
  MyException(int key, component_type type) : key_(key), type_(type) {}
  std::string& msg() noexcept { return msg_; }
  std::string what() const {
    std::stringstream ss;
    ss << " key : " << key_ << ", type : " << static_cast<int>(type_) << " : "
       << msg_;
    return ss.str();
  }

 private:
  int key_;
  component_type type_;
  std::string msg_;
};

std::string get_name_from_type(component_type) { return "name"; }

int transmit(std::string& name) {
  throw std::runtime_error(name + " is bad");
  return 1;
}

int funca(int key, component_type type) {
  try {
    auto name = get_name_from_type(type);
    return transmit(name);
  } catch (const std::runtime_error& e) {
    MyException myexcept{key, type};
    myexcept.msg() = e.what();
    throw myexcept;
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
