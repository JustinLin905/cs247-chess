#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include <map>
#include <vector>

#include "../ObserverPattern/Subject.h"
#include "../Piece/PieceTypes/Bishop.h"
#include "../Piece/PieceTypes/King.h"
#include "../Piece/PieceTypes/Knight.h"
#include "../Piece/PieceTypes/Pawn.h"
#include "../Piece/PieceTypes/Queen.h"
#include "../Piece/PieceTypes/Rook.h"
#include "Square.h"

class ChessBoard : public Subject {
    std::array<std::array<std::shared_ptr<Square>, 8>, 8> _board;
    std::map<Position, std::vector<std::weak_ptr<Piece>>> attack_map;
    std::vector<std::shared_ptr<Piece>> _white_alive_pieces;
    std::vector<std::shared_ptr<Piece>> _black_alive_pieces;
    std::shared_ptr<King> _white_king;
    std::shared_ptr<King> _black_king;

   public:
    ChessBoard();
    Square &getSquare(Position position);
    std::shared_ptr<Square> getSquarePtr(Position position);
    char getState(int row, int col) const;
    void render();
    void addPieceToBoard(char c, Position pos, std::shared_ptr<ChessBoard> chessBoard);
    void defaultSetup(std::shared_ptr<ChessBoard> chessBoard);
    void customSetup(std::shared_ptr<ChessBoard> chessBoard);
    bool hasValidMove(Color color) const;
    void updateAttackMap();
    bool isPositionUnderAttack(Position position, Color color) const;
    void removeDeadPiece(std::shared_ptr<Piece> piece);
    std::vector<std::shared_ptr<Piece>> getAlivePieces(Color color) const;
    std::shared_ptr<King> getKing(Color color) const;
    void setAlivePieces(std::vector<std::shared_ptr<Piece>> pieces, Color color);
    void reset();
};

#endif