#include "ComputerLevel4.h"

#include "../../Move/Move.h"
#include "../../Game/Game.h"
#include <vector>
#include <set>

ComputerLevel4::ComputerLevel4(Color color, std::weak_ptr<ChessBoard> chess_board, std::weak_ptr<Game> game) : ComputerPlayer(color, chess_board, game) {}

Move ComputerLevel4::getMove() {
    // wait for command to make computer move
    Move computerMoveInput = CommandInterpreter::processComputerInput();
    if (computerMoveInput.type == MoveType::INVALID) return computerMoveInput;
    
    int maxScore = INT16_MIN;
    std::unordered_set<Move> bestMoves;
    std::unordered_set<Move> validCheckMoves;

    for(auto piece : _chess_board.lock()->getAlivePieces(_color)) {
        for(auto move : piece->getValidMoves()) {
            
            // simulate the move
            SimulateMoveInfo moveInfo = _game.lock()->simulateMove(move, _color);

            // update max score move
            if (moveInfo.boardScore > maxScore) {
                maxScore = moveInfo.boardScore;
                bestMoves.clear();
                bestMoves.insert(move);
            } else if (moveInfo.boardScore == maxScore) bestMoves.insert(move);

            if (moveInfo.isOpponentInCheck) validCheckMoves.insert(move);
        }
    }

    if (!validCheckMoves.empty()) return getRandomMove(validCheckMoves);
    return getRandomMove(bestMoves);
}
