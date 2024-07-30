#ifndef ENUMS_H
#define ENUMS_H

#include <iostream>

enum class Color { WHITE, BLACK };

std::ostream& operator<<(std::ostream& out, Color& col);
std::istream& operator>>(std::istream& in, Color& color);

#endif