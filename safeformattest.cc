/*
* Typesafe printf-like wrapper around std streams
* by Igor Kozyrenko, 2013
*/

#include "safeformat.h"

#include <iostream>

size_t test_id = 0;

void test(const std::string& got, const std::string& expected,
          size_t id = ++test_id) {
  if (got != expected) {
    std::cout<<"Test "<<id<<" failed:"
               " expected \""<<expected<<"\""
               ", got: \""<<got<<"\"\n";
  } else {
    std::cout<<"Test "<<id<<" passed\n";
  }
}

void wtest(const std::wstring& got, const std::wstring& expected,
          size_t id = ++test_id) {
  if (got != expected) {
    std::wcout<<L"Test "<<id<<L" failed:"
               L" expected \""<<expected<<L"\""
               L", got: \""<<got<<L"\"\n";
  } else {
    std::wcout<<L"Test "<<id<<L" passed\n";
  }
}

int main() {
  using namespace typesafe_format;
  test(format("No nesting {0}", "allowed{1}", "it's safe"),
              "No nesting allowed{1}");
  test(format("Parameter {0} {2} {1}", "order", "random", "is"),
              "Parameter order is random");
  int* dummy = reinterpret_cast<int*>(42);
  test(format("Pointers are conscious: {0}", ptr(dummy)),
              "Pointers are conscious: 0x2a");
  test(format("Not obliged to {1} {0}", "unnecessary", "mention", "unneeded"),
              "Not obliged to mention unnecessary");
  test(format("Pass {0} or get {1} error", "enough parameters"),
              "Pass enough parameters or get {Parameter 1 is missing} error");
  test(format("Can use parameter {0} many times {0} you want", "as"),
              "Can use parameter as many times as you want");
  test(format("{0} can be escaped: {{1} ", "Left curly brace", 42),
              "Left curly brace can be escaped: {1} ");
  test(format("Can output in {{{0}}", "curly braces"),
              "Can output in {curly braces}");
  test(format("Only {{ placeholder-like }} things {0}", "should be escaped"),
              "Only {{ placeholder-like }} things should be escaped");
  test(format("Must not escape {{{0}}}", "right curly brace"),
              "Must not escape {right curly brace}}");
  test(format("Up to 10 parameters allowed: {0}{1}{2}{3}{4}{5}{6}{7}{8}{9}",
              1,2,3,4,5,6,7,8,9,0),
              "Up to 10 parameters allowed: 1234567890");
  wtest(format(L"Wide strings are {0}", "welcome here"),
               L"Wide strings are welcome here");
  std::string stdstring = "std::strings {0} {1}";
  test(format(stdstring, "are also", "supported"),
              "std::strings are also supported");
  std::wstring stdwstring = L"std::wstrings are also {0}";
  wtest(format(stdwstring, std::wstring(L"our friends")),
               L"std::wstrings are also our friends");
  test(format("Courner case {0", "courner"), "Courner case {0");
  test(format("{0}", 5), "5");
  test(format("{0", 5), "{0");
  test(format("{{{0}", ":)"), "{:)");
  test(format("{1}, {0}", "World!", "Hello"), "Hello, World!");
  test(format("{{{{{{{{{{{{{{{{ {{{{{0}}} }}}}}}}}}}}}}}}}", "}nice{"),
             "{{{{{{{{{{{{{{{{ {{}nice{}} }}}}}}}}}}}}}}}}");
  return 0;
}
