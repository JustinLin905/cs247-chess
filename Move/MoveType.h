#ifndef MOVE_TYPE_H
#define MOVE_TYPE_H

enum class MoveType {
    DEFAULT,
    QUEEN_SIDE_CASTLE,
    KING_SIDE_CASTLE,
    ENPASSANT,
    PROMOTION,
    UNDETERMINED,
};

#endif