# ftl

[![codecov](https://codecov.io/gh/ftlorg/ftl/branch/master/graph/badge.svg)](https://codecov.io/gh/ftlorg/ftl)
[![Build Status](https://travis-ci.com/ftlorg/ftl.svg?branch=master)](https://travis-ci.com/github/ftlorg/ftl)
![CMake](https://github.com/ftlorg/ftl/workflows/CMake/badge.svg)

# Overview
FTL is a C++17-based library that provides a more convenient API for collections processing. The API is heavily inspired by the Rust programming language.

# Basic usage
Collection processing with FTL is very easy. Below you can find a simple example presenting the power of the FTL.

```cpp
struct Tree { 
    enum Kind { Oak, Acer, Pine, Other };
    int height;
    int diameter;
    Kind kind;
    int volume() const;
};

ftl::vector<Tree> cityTrees{...};
int oakVolSum = 0;

// Old-school style
for (const auto& tree: cityTrees) {
  if (tree.kind == Tree::Oak) {
    if (tree.diameter > 25) 
        oakVolSum += tree.volume();
  }
}

// FTL style
const auto totalVolume = cityTrees.iter()
               .filter([](const auto &tree) { return tree.kind == Tree::Oak && tree.diameter > 25; })
               .map([](const auto &tree) { return tree.volume(); })
               .sum();
```

# Dependencies

- A C++ compiler that supports C++17
- CMake 3.17+
- Conan

# Optional Dependencies

- Doxygen
- ccache
- clang-tidy
- Cppcheck
- include-what-you-use


# Contributing
Contributions are very welcome! Either by reporting issues or submitting pull requests.

# License and Attribution
FTL is licensed under the terms of the Boost Software Licence 1.0 - see [LICENSE](./LICENSE)
