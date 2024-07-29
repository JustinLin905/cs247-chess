#include "Pawn.h"

#include "../../Manager/Manager.h"

Pawn::Pawn(Color color, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square) : Piece(color, board, square) {}

char Pawn::getPieceChar() const { return _color == Color::WHITE ? 'P' : 'p'; }

void Pawn::getEnPassantMoves(std::unordered_set<Move>& moves, Position current_pos) const {
    Position currentPos = getSquare()->getPosition();
    int row = currentPos.r;
    int col = currentPos.c;
    auto temp_board_ptr = _board.lock();

    auto check_en_passant = [&](Position opponent_pawn_pos) {
        char opponent_pawn_char = _color == Color::WHITE ? 'p' : 'P';
        char end_row = _color == Color::WHITE ? 2 : 5;
        if (temp_board_ptr->getSquare(opponent_pawn_pos).getPiece() == nullptr) return;
        auto piece = temp_board_ptr->getSquare(opponent_pawn_pos).getPiece();
        std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(piece);
        if (piece->getPieceChar() == opponent_pawn_char && pawn->movedTwoPreviously()) moves.insert(Move{current_pos, Position{end_row, opponent_pawn_pos.c}, MoveType::ENPASSANT});
    };

    if (col > 0 && temp_board_ptr->getSquare(Position{row, col - 1}).getPiece() != nullptr) check_en_passant(Position{row, col - 1});
    if (col < 7 && temp_board_ptr->getSquare(Position{row, col + 1}).getPiece() != nullptr) check_en_passant(Position{row, col + 1});
}

std::unordered_set<Position> Pawn::getAttackedSquares() const {
    std::unordered_set<Position> attackedSquares;
    Position currentPos = getSquare()->getPosition();
    int row = currentPos.r;
    int col = currentPos.c;

    // only attacked squares if there's a piece there
    auto temp_board_ptr = _board.lock();

    if (_color == Color::WHITE) {
        if (row > 0 && col > 0 && temp_board_ptr->getSquare(Position{row - 1, col - 1}).getPiece() != nullptr) attackedSquares.insert(Position{row - 1, col - 1});
        if (row > 0 && col < 7 && temp_board_ptr->getSquare(Position{row - 1, col + 1}).getPiece() != nullptr) attackedSquares.insert(Position{row - 1, col + 1});
    } else {
        if (row < 7 && col > 0 && temp_board_ptr->getSquare(Position{row + 1, col - 1}).getPiece() != nullptr) attackedSquares.insert(Position{row + 1, col - 1});
        if (row < 7 && col < 7 && temp_board_ptr->getSquare(Position{row + 1, col + 1}).getPiece() != nullptr) attackedSquares.insert(Position{row + 1, col + 1});
    }

    // en passant
    // int en_passant_row = _color == Color::WHITE ? 3 : 4;

    Position nextPos = _color == Color::WHITE ? Position{row - 1, col} : Position{row + 1, col};
    if (temp_board_ptr->getSquare(nextPos).getPiece() == nullptr) attackedSquares.insert(nextPos);  // default attack

    if (!_moved) {
        Position nextPos2 = _color == Color::WHITE ? Position{row - 2, col} : Position{row + 2, col};
        if (temp_board_ptr->getSquare(nextPos2).getPiece() == nullptr) attackedSquares.insert(nextPos2);
    }

    return attackedSquares;
}

bool Pawn::movedTwoPreviously() const {
    auto prev_move_final = Manager::getCurrGame()->getLastMove(_color);
    auto initial_pos = prev_move_final.initial_pos;
    auto final_pos = prev_move_final.final_pos;
    std::cout << "HERE4" << std::endl;

    auto prev_move_piece = _board.lock()->getSquare(final_pos).getPiece();
    std::cout << "HERE3" << std::endl;

    // prev_move_piece should never be nullptr
    return prev_move_piece->getPieceChar() == getPieceChar() && abs(initial_pos.r - final_pos.r) == 2;
}

/*
Only has move for moving forward by one square.
TODO: NEED UPDATE
*/
std::unordered_set<Move> Pawn::getValidMoves() const {
    Position current_pos = getSquare()->getPosition();
    int row = current_pos.r;
    int col = current_pos.c;
    // Position nextPos = _color == Color::WHITE ? Position{row - 1, col} : Position{row + 1, col};
    std::unordered_set<Move> validMoves;
    std::unordered_set<Position> attackedSquares = getAttackedSquares();

    for (Position p : attackedSquares) {
        if (!Manager::getCurrGame()->simulateLegality(Move{current_pos, p, MoveType::DEFAULT}, _color)) continue;
        validMoves.insert(Move{current_pos, p, MoveType::DEFAULT});
    }

    if ((_color == Color::WHITE && row == 3) || (_color == Color::BLACK && row == 4)) getEnPassantMoves(validMoves, current_pos);

    return validMoves;
}