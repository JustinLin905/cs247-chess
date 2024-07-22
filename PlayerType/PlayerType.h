#ifndef PLAYER_TYPE_H
#define PLAYER_TYPE_H

struct PlayerType {
   public:
    enum class Type {
        HUMAN,
        COMPUTER1,
        COMPUTER2,
        COMPUTER3,
        COMPUTER4
    };

    static Tye HashPlayerType(const std::string& type) {
        if (type == "human") {
            return Tye::HUMAN;
        } else if (type == "computer1") {
            return Tye::COMPUTER1;
        } else if (type == "computer2") {
            return Tye::COMPUTER2;
        } else if (type == "computer3") {
            return Tye::COMPUTER3;
        } else if (type == "computer4") {
            return Tye::COMPUTER4;
        } else {
            return Tye::HUMAN;
        }
    }
};

#endif