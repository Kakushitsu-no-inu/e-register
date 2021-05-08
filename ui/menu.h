#pragma once

#include <cassert>
#include <cstddef>
#include <tuple>
#include <type_traits>

struct IMenu
{
	virtual void switchWindow(size_t) = 0;

	virtual void print() = 0;
};

struct WindowHandleFunctor
{
	IMenu* t;
	size_t index;

	WindowHandleFunctor(IMenu* t, size_t index) : t(t), index(index)
	{}

	template <typename T>
	void operator()(T& tt) const
	{
		tt.handle(index, t);
	}
};

/**
 * @brief Функтор для друкування меню вікна 
 */
struct WindowPrintFunctor
{
	template <typename T>
	void operator()(T& t) const
	{
		t.print();
	}
};

/** 
 * @brief Обирає вікно і викликає до нього функтор 
 * @see https://stackoverflow.com/questions/8194227/how-to-get-the-i-th-element-from-an-stdtuple-when-i-isnt-know-at-compile-time
 * @note Дякую stacloverflow
*/
template <size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type for_index(int, std::tuple<Tp...>&, FuncT) {};

// clang-format off
template <std::size_t I = 0, typename FuncT, typename... Tp>
	inline typename std::enable_if< I< sizeof...(Tp), void>::type for_index(int index, std::tuple<Tp...>& t, FuncT f)
{
	if (index == 0)
		f(std::get<I>(t));
	for_index<I + 1, FuncT, Tp...>(index - 1, t, f);
};

// clang-format on

template <typename... windows_t>
struct Menu : public IMenu
{
	std::tuple<windows_t...> windows;
	size_t current = 0;

	explicit Menu(std::tuple<windows_t...> windows) : windows(std::move(windows))
	{}

	void switchWindow(size_t i) override
	{
		assert(i < sizeof...(windows_t));
		current = i;
	}

	void print() override
	{
		for_index(current, windows, WindowPrintFunctor());
	}

	void handle(size_t option)
	{
		for_index(current, windows, WindowHandleFunctor(this, option));
	}


template <typename... Windows>
constexpr auto make_menu(Windows... w) -> Menu<Windows...>
{
	return Menu<Windows...>(std::make_tuple(w...));
};