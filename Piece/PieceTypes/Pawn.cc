#include "Pawn.h"

Pawn::Pawn(Color color, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square) : Piece(color, board, square) {}

char Pawn::getPieceChar() const { return _color == Color::WHITE ? 'P' : 'p'; }

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

    Position nextPos = _color == Color::WHITE ? Position{row - 1, col} : Position{row + 1, col};
    if (temp_board_ptr->getSquare(nextPos).getPiece() == nullptr) attackedSquares.insert(nextPos);  // default attack

    if (!_moved) {
        Position nextPos2 = _color == Color::WHITE ? Position{row - 2, col} : Position{row + 2, col};
        if (temp_board_ptr->getSquare(nextPos2).getPiece() == nullptr) attackedSquares.insert(nextPos2);
    }

    return attackedSquares;
}

/*
Replaces the pawn with a piece of the player's choosing.
*/
void Pawn::promote() {
    std::shared_ptr<Piece> this_piece = getSquare()->getPiece();

    // remove pawn from player's list of pieces
    std::shared_ptr<ChessBoard> board_ptr = _board.lock();
    if (board_ptr == nullptr) {
        std::cerr << "Error: board_ptr is null in Pawn::promote()" << std::endl;
        return;
    }

    board_ptr->removeDeadPiece(this_piece);
    getSquare()->disconnectPiece();

    // get player's choice of piece
    PromotionType::Type promotion_choice = CommandInterpreter::processPromotionInput();

    // create new piece at the same location
    std::shared_ptr<Piece> new_piece;
    switch (promotion_choice) {
        case PromotionType::Type::QUEEN:
            new_piece = std::make_shared<Queen>(_color, _board, getSquare());
            break;
        case PromotionType::Type::ROOK:
            new_piece = std::make_shared<Rook>(_color, _board, getSquare());
            break;
        case PromotionType::Type::BISHOP:
            new_piece = std::make_shared<Bishop>(_color, _board, getSquare());
            break;
        case PromotionType::Type::KNIGHT:
            new_piece = std::make_shared<Knight>(_color, _board, getSquare());
            break;
        default:
            std::cerr << "Error: invalid promotion choice in Pawn::promote()" << std::endl;
            return;
    }

    getSquare()->setPiece(new_piece);
    board_ptr->addToAlivePieces(new_piece, _color);
}

/*
Only has move for moving forward by one square.
TODO: NEED UPDATE
*/
// std::unordered_set<Move> Pawn::getValidMoves() const {
//     Position currentPos = getSquare()->getPosition();
//     int row = currentPos.r;
//     int col = currentPos.c;
//     Position nextPos = _color == Color::WHITE ? Position{row - 1, col} : Position{row + 1, col};

//     return std::unordered_set<Move>{Move{currentPos, nextPos, MoveType::UNDETERMINED}};
// }