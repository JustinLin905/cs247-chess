#include "ComputerLevel4.h"

#include "../../Move/Move.h"
#include <vector>
#include <set>

ComputerLevel4::ComputerLevel4(Color color, std::weak_ptr<ChessBoard> chess_board, std::weak_ptr<Game> game) : ComputerPlayer(color, chess_board, game) {}

Move ComputerLevel4::getMove() {

    int maxScore = INT16_MIN;
    Move bestMove = Move{Position{-1, -1}, Position{-1, -1}};

    for(auto piece : _chess_board.lock()->getAlivePieces(_color)) {
        
        for(auto move : piece->getValidMoves()) {
            
            // simulate the move and get the board score after move is made
            int moveScore = _game.lock()->simulateLegality(move, _color).second;

            // update max score move
            if (moveScore > maxScore) {
                maxScore = moveScore;
                bestMove = move;
            }
        }
    }

    return bestMove;
}
