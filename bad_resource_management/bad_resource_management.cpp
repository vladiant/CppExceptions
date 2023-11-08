#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

class StreamingException {};

std::ostream OStream(std::cout.rdbuf());

int printTaggedDataDumpEntries(std::ostream&, FILE*) { return 1; }

int process_file(const std::string& fileName_) {
  FILE* f = ::fopen(fileName_.c_str(), "r");
  ::fseek(f, 0, SEEK_END);
  int file_length = ::ftell(f);
  ::rewind(f);
  int rc;
  try {
    do {
      rc = printTaggedDataDumpEntries(OStream, f);
    } while (!::feof(f) && ::ftell(f) < file_length);

    return rc;
  } catch (const StreamingException& e) {
    ::fclose(f);
    throw;
  } catch (const std::exception& e) {
    ::fclose(f);
    throw;
  }
}
int main() {
  bool stay_active = true;
  while (stay_active) {
    try {
      process_file("system.cfg");
    } catch (const std::exception& s) {
      std::cout << "error : " << s.what() << std::endl;
    } catch (...) {
      std::cout << "Unknown error : " << std::endl;
    }
    stay_active = false;
  }
}
