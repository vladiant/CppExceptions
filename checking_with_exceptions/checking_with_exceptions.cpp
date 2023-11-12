#include <cassert>
#include <future>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include <stdexcept>

class MyException {
public:
    MyException(std::string str):err_str(std::move(str)){}
    std::string& what() noexcept {return err_str;}
    const std::string& what() const noexcept {return err_str;}
private:
    std::string err_str;
};

class Request {};
class Response {};
class Service {
    public:
    Response send(const Request&) { return Response{};}
};

Service service;

void check_response(const Response&) {
    throw MyException("Bad Response");
}

Response make_error_response(const Response& resp) {
   return resp;
}

Response execute(const Request& req) {
    auto resp = service.send(req);
    try {
       check_response(resp);
    }
    catch(MyException& e) {
        std::cerr << "Error : " << e.what() << std::endl;
        return make_error_response(resp);
        throw;
    }
    return resp;
}


int main() {
    try {
       execute(Request{});
    }
    catch(...) {
        std::cout << "Unknown exception" << std::endl;
    }
    std::cout << "End" << std::endl;
}
