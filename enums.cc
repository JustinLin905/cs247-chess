#include "enums.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, Color& col) {
    out << (col == Color::WHITE ? "WHITE" : "BLACK");
    return out;
}

std::istream& operator>>(std::istream& in, Color& color) {
    std::string input;
    in >> input;
    
    if (input == "WHITE" || input == "white") {
        color = Color::WHITE;
    } else if (input == "BLACK" || input == "black") {
        color = Color::BLACK;
    }
    
    return in;
}
