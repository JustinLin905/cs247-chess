#include "ComputerLevel3.h"

#include "../../Move/Move.h"
#include <vector>
#include <set>

ComputerLevel3::ComputerLevel3(Color color, std::weak_ptr<ChessBoard> chess_board, std::weak_ptr<Game> game) : ComputerPlayer(color, chess_board, game) {}

Move ComputerLevel3::getMove() {
    
    // wait for command to make computer move
    Move computerMoveInput = CommandInterpreter::processComputerInput();
    if (computerMoveInput.type == MoveType::INVALID) return computerMoveInput;

    std::shared_ptr<ChessBoard> chess_board = _chess_board.lock();
    std::unordered_set<Move> validMoves;
    std::unordered_set<Move> validCaptureMoves;
    std::unordered_set<Move> validAvoidCaptureMoves;

    // get all pieces under attack
    for(auto piece : chess_board->getAlivePieces(_color)) {
        for(auto move : piece->getValidMoves()) {

            validMoves.insert(move); // for Computer Level 1

            if (move.type == MoveType::ENPASSANT) validCaptureMoves.insert(move); // all empassant moves are capture moves
            else {
                // if the final position of the move lands on an non-empty square, it's a capture move
                if (_chess_board.lock()->getSquare(move.final_pos).getPiece() != nullptr) validCaptureMoves.insert(move);
            }

            // check if current piece is under attack, try to avoid being captured
            Color opponent_color = (_color == Color::WHITE) ? Color::BLACK : Color::WHITE;
            if (chess_board->isPositionUnderAttack(move.initial_pos, opponent_color) && !chess_board->isPositionUnderAttack(move.final_pos, opponent_color)) {
                validAvoidCaptureMoves.insert(move);
            }
        }
    }

    if (!validAvoidCaptureMoves.empty()) return getRandomMove(validAvoidCaptureMoves); // Computer Level 3
    if (!validCaptureMoves.empty()) return getRandomMove(validCaptureMoves); // Computer Level 2
    return getRandomMove(validMoves); // Computer Level 1
}