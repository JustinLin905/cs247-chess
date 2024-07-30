#ifndef PROMOTION_CMDS_H
#define PROMOTION_CMDS_H

struct PromotionType {
   public:
    enum class Type {
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT
    };

    static Type HashPromotionType(const char type) {
        char t = tolower(type);
        if (t == 'q') {
            return Type::QUEEN;
        } else if (t == 'r') {
            return Type::ROOK;
        } else if (t == 'b') {
            return Type::BISHOP;
        } else if (t == 'k') {
            return Type::KNIGHT;
        } else {
            return Type::QUEEN;
        }
    }
};

#endif