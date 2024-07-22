#ifndef PLAYER_TYPE_H
#define PLAYER_TYPE_H

#include <string>

struct PlayerType {
   public:
    enum class Type {
        HUMAN,
        COMPUTER1,
        COMPUTER2,
        COMPUTER3,
        COMPUTER4
    };

    static Type HashPlayerType(const std::string& type) {
        if (type == "human") {
            return Type::HUMAN;
        } else if (type == "computer1") {
            return Type::COMPUTER1;
        } else if (type == "computer2") {
            return Type::COMPUTER2;
        } else if (type == "computer3") {
            return Type::COMPUTER3;
        } else if (type == "computer4") {
            return Type::COMPUTER4;
        } else {
            return Type::HUMAN;
        }
    }
};

#endif