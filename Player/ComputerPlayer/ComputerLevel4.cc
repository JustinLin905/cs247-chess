#include "ComputerLevel4.h"

#include <set>
#include <vector>

#include "../../Game/Game.h"
#include "../../Move/Move.h"
#include "../../enums.h"

ComputerLevel4::ComputerLevel4(Color color, std::weak_ptr<ChessBoard> chess_board, std::weak_ptr<Game> game) : ComputerPlayer(color, chess_board, game) {}

Move ComputerLevel4::getMove() {
    // wait for command to make computer move
    Move computerMoveInput = CommandInterpreter::processComputerInput();
    if (computerMoveInput.type == MoveType::INVALID) return computerMoveInput;
    float maxScore = INT16_MIN;
    std::shared_ptr<ChessBoard> chess_board = _chess_board.lock();
    std::unordered_set<Move> bestMoves;
    std::unordered_set<Move> validCheckMoves;

    for (auto piece : chess_board->getAlivePieces(_color)) {
        char c = piece->getPieceChar();

        for (auto move : piece->getValidMoves()) {
            // simulate the move
            SimulateMoveInfo moveInfo = _game.lock()->simulateMove(move, _color);
            float curMoveScore = moveInfo.boardScore;

            // if move avoids being captured, add to board score to give it priority
            Color opponent_color = (_color == Color::WHITE) ? Color::BLACK : Color::WHITE;
            if (chess_board->isPositionUnderAttack(move.initial_pos, opponent_color) && !chess_board->isPositionUnderAttack(move.final_pos, opponent_color)) {
                int pieceVal = (chess_board->piece_score.find(std::toupper(c)) == chess_board->piece_score.end()) ? 0 : chess_board->piece_score.at(std::toupper(c));
                curMoveScore += pieceVal;
            }

            // update max score move
            if (curMoveScore > maxScore) {
                maxScore = curMoveScore;
                bestMoves.clear();
                bestMoves.insert(move);
            } else if (curMoveScore == maxScore) bestMoves.insert(move);

            if (moveInfo.isOpponentInCheck) validCheckMoves.insert(move);
        }
    }

    if (!validCheckMoves.empty()) return getRandomMove(validCheckMoves);
    return getRandomMove(bestMoves);
}
