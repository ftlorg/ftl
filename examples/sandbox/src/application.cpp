#include <sandbox/application.hpp>

#include <iostream>

#include <ftl/ftl.hpp>
#include <tuple>

int Application::exec() {
  struct Person {
    int32_t Age;
    bool Sex;
    std::string Name;
    std::string City;
  };

  auto people = ftl::vector<Person>{
    Person{
      34,
      true,
      "John",
      "Krakow",
    },
    Person{
      24,
      true,
      "Grzegorz",
      "Rymanow",
    },
    Person{
      26,
      false,
      "Magda",
      "Krakow",
    },
    Person{
      19,
      false,
      "Klaudia",
      "Warszawa",
    },
    Person{
      31,
      true,
      "Jan",
      "Krakow",
    },
    Person{
      27,
      true,
      "Bartosz",
      "Krakow",
    },
    Person{
      18,
      true,
      "Jakub",
      "Krakow",
    },
  };

  auto average = std::get<0>(people.iter()
                               .filter([](const auto &person) { return person.City == "Krakow" && person.Sex == true; })
                               .map([](const auto &person) { return person.Age; })
                               .fold(std::make_tuple(0.0, 1.0), [](auto acc, const auto &x) {
                                 auto &[first, second] = acc.get();
                                 return std::make_tuple(first + (x - first) / second, second + 1.0);
                               }));

  std::cout << average << "\n";

  return 0;
}
