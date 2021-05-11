#pragma once

#include "option.h"
#include <complex>
#include <cstddef>
#include <iostream>

template <size_t size> struct stage {
  const char *             title;
  std::array<option, size> options;

  stage(const char *title, const std::array<option, size> &options)
    : title{title}, options{options} {}

  void print() {
    std::cout << title << "\n";
    std::cout << "--------------------------------------------"
              << "\n";
    for (size_t i = 0; i < size; i++) {
      std::cout << i + 1 << "| " << options[i].text << "\n";
    }
    std::cout << "--------------------------------------------"
              << "\n";
  }

  void handle(size_t i, menu_base *menu) {
    if (i >= size) {
      std::cout << "Invalid Option\n";
      return;
    }
    options[i].callback(menu);
  }
};

template <typename... options> constexpr auto make_window(const char *title, options... o)
  -> stage<sizeof...(options)> {
  return stage<sizeof...(options)>(title, {o...});
};
