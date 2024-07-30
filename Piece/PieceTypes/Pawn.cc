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
        if (piece->getPieceChar() == opponent_pawn_char && pawn->movedTwoPreviously()) {
            auto move = Move{current_pos, Position{end_row, opponent_pawn_pos.c}, MoveType::ENPASSANT};
            if (Manager::getCurrGame()->simulateLegality(move, _color)) {
                moves.insert(move);
                std::cout << move << " ENPASSANT" << std::endl;
            }
        }
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
        tryAttackSquare(Position{row - 1, col - 1}, attackedSquares);
        tryAttackSquare(Position{row - 1, col + 1}, attackedSquares);
    } else {
        tryAttackSquare(Position{row + 1, col - 1}, attackedSquares);
        tryAttackSquare(Position{row + 1, col + 1}, attackedSquares);
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

    // Update attack map
    board_ptr->updateAttackMap();
}

/*
Only has move for moving forward by one square.
TODO: NEED UPDATE
*/
std::unordered_set<Move> Pawn::getValidMoves() const {
    Position current_pos = getSquare()->getPosition();
    int row = current_pos.r;
    int col = current_pos.c;
    std::unordered_set<Move> validMoves;
    std::unordered_set<Position> attackedSquares = getAttackedSquares();

    for (Position p : attackedSquares) {
        // if attacked square is empty, don't add it to valid moves
        if (_board.lock()->getSquare(p).getPiece() == nullptr) continue;

        if (!Manager::getCurrGame()->simulateLegality(Move{current_pos, p, MoveType::DEFAULT}, _color)) continue;
        validMoves.insert(Move{current_pos, p, MoveType::DEFAULT});
    }

    // default moves
    Position next_pos = _color == Color::WHITE ? Position{row - 1, col} : Position{row + 1, col};
    auto temp_board_ptr = _board.lock();
    if (next_pos.r >= 0 && next_pos.r <= 7 && temp_board_ptr->getSquare(next_pos).getPiece() == nullptr) {
        auto move = Move{current_pos, next_pos, MoveType::DEFAULT};
        if (Manager::getCurrGame()->simulateLegality(move, _color)) validMoves.insert(move);
    };  // default attack

    if (!_moved) {
        int init_row = _color == Color::WHITE ? 6 : 1;
        Position next_pos2 = _color == Color::WHITE ? Position{row - 2, col} : Position{row + 2, col};
        if (row == init_row && next_pos2.r >= 0 && next_pos2.r <= 7 && temp_board_ptr->getSquare(next_pos2).getPiece() == nullptr) {
            auto move = Move{current_pos, next_pos2, MoveType::DEFAULT};
            if (Manager::getCurrGame()->simulateLegality(move, _color)) validMoves.insert(move);
        }
    }

    if ((_color == Color::WHITE && row == 3) || (_color == Color::BLACK && row == 4)) getEnPassantMoves(validMoves, current_pos);

    return validMoves;
}