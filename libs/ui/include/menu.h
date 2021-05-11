#pragma once

#include <cassert>
#include <cstddef>
#include <tuple>
#include <type_traits>

struct menu_base {
  virtual void switch_window(size_t) = 0;
  virtual void print()               = 0;
};

struct stage_handle_functor {
  menu_base *base;
  size_t     index;

  stage_handle_functor(menu_base *base, size_t index) : base{base}, index{index} {}

  template <typename T> void operator()(T &_menu) const { _menu.handle(index, base); }
};

struct stage_print_functor {
  template <typename T> void operator()(T &_menu) const { _menu.print(); }
};

/**
 * @see
 * https://stackoverflow.com/questions/8194227/how-to-get-the-i-th-element-from-an-stdtuple-when-i-isnt-know-at-compile-time
 * @note Дякую stacloverflow
 */
template <size_t I = 0, typename Funtor, typename... Tuple> inline
  typename std::enable_if<I == sizeof...(Tuple), void>::type
  for_index(int, std::tuple<Tuple...> &, Funtor){};

template <std::size_t I = 0, typename Funtor, typename... Tuple> inline typename std::enable_if <
  I<sizeof...(Tuple), void>::type for_index(int index, std::tuple<Tuple...> &t, Funtor f) {
  if (index == 0)
    f(std::get<I>(t));
  for_index<I + 1, Funtor, Tuple...>(index - 1, t, f);
};

template <typename... Stages> struct menu : public menu_base {
  std::tuple<Stages...> windows;
  size_t                   current = 0;

  explicit menu(std::tuple<Stages...> windows) : windows(std::move(windows)) {}

  void switch_window(size_t i) override {
    assert(i < sizeof...(Stages));
    current = i;
  }

  void print() override { for_index(current, windows, stage_print_functor()); }

  void handle(size_t option) { for_index(current, windows, stage_handle_functor(this, option)); }
};

template <typename... Stages> constexpr auto make_menu(Stages... w) -> menu<Stages...> {
  return menu<Stages...>(std::make_tuple(w...));
}
