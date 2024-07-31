#include "ComputerLevel4.h"

#include "../../Move/Move.h"
#include <vector>
#include <set>

ComputerLevel4::ComputerLevel4(Color color, std::weak_ptr<ChessBoard> chess_board, std::weak_ptr<Game> game) : ComputerPlayer(color, chess_board, game) {}

Move ComputerLevel4::getMove() {
    // wait for command to make computer move
    Move computerMoveInput = CommandInterpreter::processComputerInput();
    if (computerMoveInput.type == MoveType::INVALID) return computerMoveInput;
    
    int maxScore = INT16_MIN;
    std::unordered_set<Move> bestMoves;

    for(auto piece : _chess_board.lock()->getAlivePieces(_color)) {
        for(auto move : piece->getValidMoves()) {
            
            // simulate the move and get the board score after move is made
            int moveScore = _game.lock()->simulateLegality(move, _color).second;

            // update max score move
            if (moveScore > maxScore) {
                maxScore = moveScore;
                bestMoves.clear();
                bestMoves.insert(move);
            } else if (moveScore == maxScore) bestMoves.insert(move);
        }
    }

    return getRandomMove(bestMoves);
}
