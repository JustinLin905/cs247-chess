#include "ComputerLevel2.h"

#include "../../Move/Move.h"
#include <set>
#include <random>

ComputerLevel2::ComputerLevel2(Color color, std::weak_ptr<ChessBoard> chess_board, std::weak_ptr<Game> game) : ComputerPlayer(color, chess_board, game) {}

Move ComputerLevel2::getMove() {
    // wait for command to make computer move
    Move computerMoveInput = CommandInterpreter::processComputerInput();
    if (computerMoveInput.type == MoveType::INVALID) return computerMoveInput;
    
    std::unordered_set<Move> validMoves;
    std::unordered_set<Move> validCaptureMoves;

    for(auto piece : _chess_board.lock()->getAlivePieces(_color)) {
        for(auto move : piece->getValidMoves()) {

            validMoves.insert(move); // Computer Level 1

            if (isCaptureMove(move)) validCaptureMoves.insert(move); // Computer Level 2
        }
    }

    if (!validCaptureMoves.empty()) return getRandomMove(validCaptureMoves); // Computer Level 3
    else return getRandomMove(validMoves); // Computer Level 1
}