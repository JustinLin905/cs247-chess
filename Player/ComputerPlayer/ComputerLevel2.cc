#include "ComputerLevel2.h"

#include "../../Move/Move.h"
#include <set>
#include <random>

ComputerLevel2::ComputerLevel2(Color color, std::weak_ptr<ChessBoard> chess_board) : ComputerPlayer(color, chess_board) {}

Move ComputerLevel2::getMove() {
    std::unordered_set<Move> validMoves;
    std::unordered_set<Move> validCaptureMoves;

    for(auto piece : _chess_board.lock()->getAlivePieces(_color)) {
        for(auto move : piece->getValidMoves()) {

            validMoves.insert(move);

            // if the final position of the move lands on an non-empty square, it's a capture move
            if (_chess_board.lock()->getSquare(move.final_pos).getPiece() != nullptr) validCaptureMoves.insert(move);
        }
    }

    if (validCaptureMoves.empty()) return getRandomMove(validMoves);
    else return getRandomMove(validCaptureMoves);
}