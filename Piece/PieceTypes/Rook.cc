#include "Rook.h"

#include "../../ChessBoard/ChessBoard.h"
#include "../../Manager/Manager.h"

Rook::Rook(Color color, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square) : Piece(color, board, square) {}

char Rook::getPieceChar() const { return _color == Color::WHITE ? 'R' : 'r'; }

std::unordered_set<Position> Rook::getAttackedSquares() const {
    std::unordered_set<Position> attackedSquares;
    attackStraight(attackedSquares);
    return attackedSquares;
}

std::unordered_set<Move> Rook::getValidMoves() const {
    std::unordered_set<Move> validMoves;
    std::unordered_set<Position> attackedSquares = getAttackedSquares();
    Position current_pos = getSquare()->getPosition();

    for (Position p : attackedSquares) {
        if (!Manager::getCurrGame()->simulateLegality(Move{current_pos, p, MoveType::DEFAULT}, _color).first) continue;
        validMoves.insert(Move{current_pos, p, MoveType::DEFAULT});
    }

    // getCastleMoves(validMoves, current_pos);
    return validMoves;
}