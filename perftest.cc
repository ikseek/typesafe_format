/*
* Typesafe printf-like wrapper around std streams
* by Igor Kozyrenko, 2013
*/

#include <cstdio>
#include "safeformat.h"

#include <iostream>

void snprintftest(size_t i) {
  char buff[1024];
  snprintf(buff, 1024, "String: %s, integer: %d, float: %f, pointer: %p",
    "substring", 42, 3.14, buff);
}

void formattest(size_t i) {
  char dummy;
  std::string res = 
    typesafe_format::format("String: {0}, integer: {1}, float: {2}, pointer: {3}",
    "substring", 42, 3.14, typesafe_format::ptr(&dummy));
}

void streamtest(size_t i) {
  void* ptr = 0;
  std::stringstream stream;
  stream<<"String: "<<"substring"<<", integer: "<<42<<", float: "<<3.14<<", pointer: "<<ptr;
}

void iterate(void(test)(size_t)) {
  for (size_t i = 0; i < 1000000; ++i) {
    test(i);
  }
}

int main(int argc, char* argv[]) {
  if (argc == 2 && std::string(argv[1]) == "printf") {
    iterate(snprintftest);
  } else if (argc == 2 && std::string(argv[1]) == "stream") {
    iterate(streamtest);
  }else {
    iterate(formattest);
  }
}