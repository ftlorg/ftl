#include <sandbox/application.hpp>

#include <iostream>

#include <ftl/ftl.hpp>

int Application::exec()
{
  while (true) {
    std::cout << "Calculating factorial: " << ftl::factorial(5) << "\n";
  }
}
