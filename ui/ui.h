#pragma once

#include <cstddef>
#include <iostream>
#include <complex>
#include "option.h"

template<size_t size>
struct Window {
    const char * title;
    const char * footer;
    std::array<Option, size> options;

    Window(const char *title, const char *footer, const std::array<Option, size> &options) : title(title),
                                                                                             footer(footer),
                                                                                             options(options) {}
    void print() {
        std::cout << title << "\n";
        std::cout << "--------------------------------------------" << "\n";
        for (size_t i = 0; i < size; i++) {
            std::cout << i + 1 << "| " << options[i].text << "\n";
        }
        std::cout << "--------------------------------------------" << "\n";
        std::cout << footer << "\n";
    }

    void handle(size_t i, IMenu * menu){
        if(i >= size){
            std::cout << "Invalid Option\n";
            return;
        }
        options[i].callback(menu);
    }
};

template<typename ...options>
constexpr auto make_window(const char * title, const char * footer, options... o) -> Window<sizeof...(options)>{
    return Window<sizeof...(options)>(title, footer, {o...});
};
