#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

struct FileManager {
  FileManager(const std::string& fileName_)
      : fptr{::fopen(fileName_.c_str(), "r")} {};
  ~FileManager() { ::fclose(fptr); }
  FILE* fptr;
};

class StreamingException {};

std::ostream OStream(std::cout.rdbuf());

int printTaggedDataDumpEntries(std::ostream&, FILE*) { return 1; }

int process_file(const std::string& fileName_) {
  FileManager fmgr{fileName_};
  FILE* f = fmgr.fptr;
  ::fseek(f, 0, SEEK_END);
  int file_length = ::ftell(f);
  ::rewind(f);
  int rc;

  do {
    rc = printTaggedDataDumpEntries(OStream, f);
  } while (!::feof(f) && ::ftell(f) < file_length);

  return rc;
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
