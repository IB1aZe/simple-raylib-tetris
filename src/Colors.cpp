#include <vector>
#include "Colors.hpp"

const Color darkGray = {50, 50, 50, 255};
const Color green = {0, 255, 0, 255};
const Color red = {255, 0, 0, 255};
const Color orange = {255, 165, 0, 255};
const Color yellow = {255, 255, 0, 255};
const Color purple = {128, 0, 128, 255};
const Color cyan = {0, 255, 255, 255};
const Color blue = {0, 0, 255, 255};
const Color lightBlue = {59, 85, 162, 255};
const Color darkBlue = {44, 44, 127, 255};

std::vector<Color> GetCellColors()
{
    return {darkGray, green, red, orange, yellow, purple, cyan, blue};
}