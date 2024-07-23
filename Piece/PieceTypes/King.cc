#include "King.h"

King::King(Color color, std::shared_ptr<Player> player,
           std::shared_ptr<ChessBoard> board)
    : Piece(color, player, board) {}

char King::getPieceChar() const { return _color == Color::WHITE ? 'K' : 'k'; }