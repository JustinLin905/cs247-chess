#include "Rook.h"

#include "../../ChessBoard/ChessBoard.h"

Rook::Rook(Color color, Player* player, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square)
    : Piece(color, player, board, square) {}

char Rook::getPieceChar() const { return _color == Color::WHITE ? 'R' : 'r'; }

std::unordered_set<Position> Rook::getAttackedSquares() const {
    std::unordered_set<Position> attackedSquares;
    attackStraight(attackedSquares);
    return attackedSquares;
}

void Rook::getCastleMoves(std::unordered_set<Move>& validMoves, Position current_pos) const {
    if (_moved) return;

    auto temp_board_ref = _board.lock();

    int row = _color == Color::WHITE ? 7 : 0;

    char king_char = _color == Color::WHITE ? 'K' : 'k';
    int king_col = 4;
    auto piece_at_king = temp_board_ref->getSquare(Position{row, king_col}).getPiece();  // piece currently at the king's position

    if (piece_at_king->getPieceChar() != king_char || piece_at_king->hasMoved()) return;  // if the king has moved, we can't castle

    if (current_pos == Position{row, 0}) {
        for (int i = 1; i < 4; i++) {
            if (temp_board_ref->getSquare(Position{row, i}).getPiece() != nullptr) return;
        }

        validMoves.insert(Move{current_pos, Position{row, 3}, MoveType::QUEEN_SIDE_CASTLE});
    } else if (current_pos == Position{row, 7}) {
        for (int i = 5; i < 7; i++) {
            if (temp_board_ref->getSquare(Position{row, i}).getPiece() != nullptr) return;
        }

        validMoves.insert(Move{current_pos, Position{row, 5}, MoveType::KING_SIDE_CASTLE});
    }
}

std::unordered_set<Move> Rook::getValidMoves() const {
    std::unordered_set<Move> validMoves;
    std::unordered_set<Position> attackedSquares = getAttackedSquares();
    Position current_pos = getSquare()->getPosition();

    for (Position p : attackedSquares) validMoves.insert(Move{current_pos, p, MoveType::DEFAULT});

    getCastleMoves(validMoves, current_pos);
    return validMoves;
}