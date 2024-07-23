#include "Piece.h"

#include "../ChessBoard/ChessBoard.h"
#include "../ChessBoard/Square.h"
#include "../Player/Player.h"

Piece::Piece(Color color, std::shared_ptr<Player> player,
             std::shared_ptr<ChessBoard> board)
    : _player(player), _color(color), _board(board) {}

Color Piece::getColor() const { return _color; }
