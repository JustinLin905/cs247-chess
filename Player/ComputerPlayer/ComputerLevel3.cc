#include "ComputerLevel3.h"

#include "../../Move/Move.h"
#include <vector>
#include <set>

ComputerLevel3::ComputerLevel3(Color color, std::weak_ptr<ChessBoard> chess_board) : ComputerPlayer(color, chess_board) {}

Move ComputerLevel3::getMove() {
    std::shared_ptr<ChessBoard> chess_boad = _chess_board.lock();
    std::unordered_set<Move> validMoves;
    std::unordered_set<Move> validCaptureMoves;
    std::unordered_set<Move> validAvoidCaptureMoves;

    // get all pieces under attack
    for(auto piece : chess_boad->getAlivePieces(_color)) {
        for(auto move : piece->getValidMoves()) {

            validMoves.insert(move); // for Computer Level 1

            // if the final position of the move lands on an non-empty square, it's a capture move (for Computer Level 2)
            if (chess_boad->getSquare(move.final_pos).getPiece() != nullptr) validCaptureMoves.insert(move);

            // check if current piece is under attack, try to avoid being captured
            Color opponent_color = (_color == Color::WHITE) ? Color::BLACK : Color::WHITE;
            if (chess_boad->isPositionUnderAttack(move.initial_pos, opponent_color) && !chess_boad->isPositionUnderAttack(move.final_pos, opponent_color)) {
                validAvoidCaptureMoves.insert(move);
            }
        }

    }

    if (!validAvoidCaptureMoves.empty()) return getRandomMove(validAvoidCaptureMoves); // Computer Level 3
    if (!validCaptureMoves.empty()) return getRandomMove(validCaptureMoves); // Computer Level 2
    return getRandomMove(validMoves); // Computer Level 1
}