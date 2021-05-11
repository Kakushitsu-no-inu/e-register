#pragma once

#include "menu.h"
#include <functional>
#include <utility>

struct option {
  using callback_t = std::function<void(menu_base *)>;

  callback_t  callback;
  const char *text;

  option(callback_t callback, const char *text) : callback{std::move(callback)}, text{text} {}
};
