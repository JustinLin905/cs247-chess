#include "ComputerLevel1.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

#include "../../Move/Move.h"

ComputerLevel1::ComputerLevel1(Color color, std::weak_ptr<ChessBoard> chess_board, std::weak_ptr<Game> game) : ComputerPlayer(color, chess_board, game) {}

Move ComputerLevel1::getMove() {
    // wait for command to make computer move
    Move computerMoveInput = CommandInterpreter::processComputerInput();
    if (computerMoveInput.type == MoveType::INVALID) return computerMoveInput;
    
    std::unordered_set<Move> validMoves;
    for(auto piece : _chess_board.lock()->getAlivePieces(_color)) {
        validMoves.insert(piece->getValidMoves().begin(), piece->getValidMoves().end());
    }

    return getRandomMove(validMoves);
}