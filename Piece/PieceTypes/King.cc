#include "King.h"

#include "../../Manager/Manager.h"
#include "../../Player/Player.h"

King::King(Color color, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square) : Piece(color, board, square) {}

char King::getPieceChar() const { return _color == Color::WHITE ? 'K' : 'k'; }

std::unordered_set<Position> King::getAttackedSquares() const {
    std::unordered_set<Position> attackedSquares;
    Position currentPos = getSquare()->getPosition();
    int row = currentPos.r;
    int col = currentPos.c;

    tryAttackSquare(Position{row - 1, col - 1}, attackedSquares);
    tryAttackSquare(Position{row - 1, col}, attackedSquares);
    tryAttackSquare(Position{row - 1, col + 1}, attackedSquares);
    tryAttackSquare(Position{row, col - 1}, attackedSquares);
    tryAttackSquare(Position{row, col + 1}, attackedSquares);
    tryAttackSquare(Position{row + 1, col - 1}, attackedSquares);
    tryAttackSquare(Position{row + 1, col}, attackedSquares);
    tryAttackSquare(Position{row + 1, col + 1}, attackedSquares);

    return attackedSquares;
}

void King::getCastleMoves(std::unordered_set<Move>& validMoves, Position current_pos) const {
    if (_moved) return;

    auto temp_board_ref = _board.lock();
    int row = _color == Color::WHITE ? 7 : 0;
    char rook_char = _color == Color::WHITE ? 'R' : 'r';
    int queen_rook_col = 0;
    int king_rook_col = 7;

    auto piece_at_queen_rook = temp_board_ref->getSquare(Position{row, queen_rook_col}).getPiece();  // piece currently at the king's position
    auto piece_at_king_rook = temp_board_ref->getSquare(Position{row, king_rook_col}).getPiece();    // piece currently at the king's position

    // if (piece_at_queen_rook == nullptr || piece_at_king_rook == nullptr) return;

    auto check_castle = [&](int start, int end) {
        for (int i = start; i <= end; i++) {
            if (temp_board_ref->getSquare(Position{row, i}).getPiece() != nullptr) return false;                                              // cannot castle through pieces
            if (temp_board_ref->isPositionUnderAttack(Position{row, i}, _color == Color::WHITE ? Color::BLACK : Color::WHITE)) return false;  // cannot castle through check
        }
        return true;
    };

    if (piece_at_queen_rook != nullptr && piece_at_queen_rook->getPieceChar() == rook_char && !piece_at_queen_rook->hasMoved()) {
        auto move = Move{current_pos, Position{row, 2}, MoveType::QUEEN_SIDE_CASTLE};
        if (check_castle(2, 3) && Manager::getCurrGame()->simulateMove(move, _color).isLegal) validMoves.insert(move);
    }

    if (piece_at_king_rook != nullptr && piece_at_king_rook->getPieceChar() == rook_char && !piece_at_king_rook->hasMoved()) {
        auto move = Move{current_pos, Position{row, 6}, MoveType::KING_SIDE_CASTLE};
        if (check_castle(5, 6) && Manager::getCurrGame()->simulateMove(move, _color).isLegal) validMoves.insert(move);
    }
}

std::unordered_set<Move> King::getValidMoves() const {
    std::unordered_set<Move> validMoves;
    std::unordered_set<Position> attackedSquares = getAttackedSquares();
    Position current_pos = getSquare()->getPosition();

    for (Position p : attackedSquares) {
        if (!Manager::getCurrGame()->simulateMove(Move{current_pos, p, MoveType::DEFAULT}, _color).isLegal) continue;
        validMoves.insert(Move{current_pos, p, MoveType::DEFAULT});
    }

    if (!inCheck()) getCastleMoves(validMoves, current_pos);
    return validMoves;
}

bool King::inCheck() const {
    Position currentPos = getSquare()->getPosition();
    Color enemy_color = _color == Color::WHITE ? Color::BLACK : Color::WHITE;
    std::shared_ptr<ChessBoard> board_shared = _board.lock();
    if (!board_shared) {
        std::cerr << "Error: Board is null" << std::endl;
        return false;
    }

    if (board_shared->isPositionUnderAttack(currentPos, enemy_color)) {
        return true;
    }

    return false;
}