#ifndef POSITION_H
#define POSITION_H

#include <cstddef>     // For size_t
#include <functional>  // For std::hash

struct Position {
    int r;
    int c;

    bool operator==(const Position &other) const {
        return r == other.r && c == other.c;
    }

    bool operator!=(const Position &other) const { return !(*this == other); }

    bool operator<(const Position &other) const {
        if (r != other.r) {
            return r < other.r;
        }
        return c < other.c;
    }
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