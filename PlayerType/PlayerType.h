#ifndef PLAYER_TYPE_H
#define PLAYER_TYPE_H

#include <string>

struct PlayerType {
   public:
    enum class Type {
        HUMAN,
        COMPUTER_LEVEL1,
        COMPUTER_LEVEL2,
        COMPUTER_LEVEL3,
        COMPUTER_LEVEL4
    };

    static Type HashPlayerType(const std::string& type) {
        if (type == "human") {
            return Type::HUMAN;
        } else if (type == "computer1") {
            return Type::COMPUTER_LEVEL1;
        } else if (type == "computer2") {
            return Type::COMPUTER_LEVEL2;
        } else if (type == "computer3") {
            return Type::COMPUTER_LEVEL3;
        } else if (type == "computer4") {
            return Type::COMPUTER_LEVEL4;
        } else {
            return Type::HUMAN;
        }
    }
};

#endif