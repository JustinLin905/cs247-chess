#ifndef POSITION_H
#define POSITION_H

#include <cstddef>     // For size_t
#include <functional>  // For std::hash

struct Position {
    int c;
    int r;

    bool operator==(const Position &other) const {
        return r == other.r && c == other.c;
    }

    bool operator!=(const Position &other) const { return !(*this == other); }
};

// Hash function for Position
namespace std {
template <>
struct hash<Position> {
    size_t operator()(const Position &pos) const {
        return std::hash<int>()(pos.r) ^ (std::hash<int>()(pos.c) << 1);
    }
};
}  // namespace std

#endif