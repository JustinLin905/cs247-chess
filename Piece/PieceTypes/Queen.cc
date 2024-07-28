#include "Queen.h"

Queen::Queen(Color color, Player* player, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square)
    : Piece(color, player, board, square) {}

char Queen::getPieceChar() const { return _color == Color::WHITE ? 'Q' : 'q'; }

std::unordered_set<Position> Queen::getAttackedSquares() const {
    std::unordered_set<Position> attacked_squares;
    attackDiagonal(attacked_squares);
    attackStraight(attacked_squares);
    return attacked_squares;
}