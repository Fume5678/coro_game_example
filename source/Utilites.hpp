#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <iostream>
#include <string>

#ifndef _RESOURCE_PATH
const std::string RESOURCE_PATH = "../resource/";
#else
const std::string RESOURCE_PATH = _RESOURCE_PATH;
#endif

const unsigned SCREEN_WIDTH  = 800;
const unsigned SCREEN_HEIGHT = 600;
const unsigned MAP_SIZE      = 256;
const unsigned CELL_SIZE     = 64;

struct Point {
    int x;
    int y;

    constexpr Point(int x, int y) : x(x), y(y) {}
    Point(const Point&)            = default;
    Point& operator=(const Point&) = default;
};

constexpr Point screen_center() {
    Point p(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    return p;
}

inline void print_func_terminate(std::string s) {
    std::cout << "TODO!: " << s << "\n";
    std::terminate();
}

#define TODO() print_func_terminate(__PRETTY_FUNCTION__)

#endif // CONSTANTS_HPP
