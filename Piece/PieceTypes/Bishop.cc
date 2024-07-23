#include "Bishop.h"

Bishop::Bishop(Color color, std::shared_ptr<Player> player,
               std::shared_ptr<ChessBoard> board)
    : Piece(color, player, board) {}

char Bishop::getPieceChar() const { return _color == Color::WHITE ? 'B' : 'b'; }