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
    
    std::array<std::array<float, 8>, 8> pawn_pos_score_b = {{
        {  0,  0,  0,  0,  0,  0,  0,  0 },
        {  5, 10, 10,-20,-20, 10, 10,  5 },
        {  5, -5,-10,  0,  0,-10, -5,  5 },
        {  0,  0,  0, 20, 20,  0,  0,  0 },
        {  5,  5, 10, 25, 25, 10,  5,  5 },
        { 10, 10, 20, 30, 30, 20, 10, 10 },
        { 50, 50, 50, 50, 50, 50, 50, 50 },
        {  0,  0,  0,  0,  0,  0,  0,  0 }
    }};

    std::array<std::array<float, 8>, 8> knight_pos_score_b = {{
        { -50, -40, -30, -30, -30, -30, -40, -50 },
        { -40, -20,   0,   5,   5,   0, -20, -40 },
        { -30,   5,  10,  15,  15,  10,   5, -30 },
        { -30,   0,  15,  20,  20,  15,   0, -30 },
        { -30,   5,  15,  20,  20,  15,   5, -30 },
        { -30,   0,  10,  15,  15,  10,   0, -30 },
        { -40, -20,   0,   0,   0,   0, -20, -40 },
        { -50, -40, -30, -30, -30, -30, -40, -50 }
    }};

    std::array<std::array<float, 8>, 8> bishop_pos_score_b = {{
        { -20, -10, -10, -10, -10, -10, -10, -20 },
        { -10,   5,   0,   0,   0,   0,   5, -10 },
        { -10,  10,  10,  10,  10,  10,  10, -10 },
        { -10,   0,  10,  10,  10,  10,   0, -10 },
        { -10,   5,   5,  10,  10,   5,   5, -10 },
        { -10,   0,   5,  10,  10,   5,   0, -10 },
        { -10,   0,   0,   0,   0,   0,   0, -10 },
        { -20, -10, -10, -10, -10, -10, -10, -20 }
    }};

    std::array<std::array<float, 8>, 8> rook_pos_score_b = {{
        {   0,   0,   5,  10,  10,   5,   0,   0 },
        {  -5,   0,   0,   0,   0,   0,   0,  -5 },
        {  -5,   0,   0,   0,   0,   0,   0,  -5 },
        {  -5,   0,   0,   0,   0,   0,   0,  -5 },
        {  -5,   0,   0,   0,   0,   0,   0,  -5 },
        {  -5,   0,   0,   0,   0,   0,   0,  -5 },
        {   5,  10,  10,  10,  10,  10,  10,   5 },
        {   0,   0,   0,   0,   0,   0,   0,   0 }
    }};

    std::array<std::array<float, 8>, 8> queen_pos_score_b = {{
        { -20, -10, -10, -5, -5, -10, -10, -20 },
        { -10,   0,   5,  0,  0,   0,   0, -10 },
        { -10,   5,   5,  5,  5,   5,   0, -10 },
        {   0,   0,   5,  5,  5,   5,   0,  -5 },
        {  -5,   0,   5,  5,  5,   5,   0,  -5 },
        { -10,   0,   5,  5,  5,   5,   0, -10 },
        { -10,   0,   0,  0,  0,   0,   0, -10 },
        { -20, -10, -10, -5, -5, -10, -10, -20 }
    }};

    std::array<std::array<float, 8>, 8> king_pos_score_b = {{
        { 20,  30,  10,  0,   0,   10,  30,  20 },
        { 20,  20,  0,   0,   0,   0,   20,  20 },
        { -10, -20, -20, -20, -20, -20, -20, -10 },
        { -20, -30, -30, -40, -40, -30, -30, -20 },
        { -30, -40, -40, -50, -50, -40, -40, -30 },
        { -30, -40, -40, -50, -50, -40, -40, -30 },
        { -30, -40, -40, -50, -50, -40, -40, -30 },
        { -30, -40, -40, -50, -50, -40, -40, -30 }
    }};


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
    void addToAlivePieces(std::shared_ptr<Piece> piece, Color color);
    void setAlivePieces(std::vector<std::shared_ptr<Piece>> pieces, Color color);
    float calculateScore(Color color);
    void reset();

    const std::map<char, float> piece_score = {
        {'P', 1},
        {'N', 3},
        {'B', 3},
        {'R', 5},
        {'Q', 9},
    };
};

#endif