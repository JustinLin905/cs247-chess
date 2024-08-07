#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "../ChessBoard/ChessBoard.h"
#include "../Move/Move.h"
#include "../ObserverPattern/GraphicsObserver.h"
#include "../ObserverPattern/TextObserver.h"
#include "../Player/Player.h"
#include "../PlayerType/PlayerType.h"

struct SimulateMoveInfo {
    bool isLegal;
    float boardScore;
    bool isOpponentInCheck;
};

class Game {
    std::shared_ptr<ChessBoard> _chess_board;
    std::shared_ptr<Player> _white;
    std::shared_ptr<Player> _black;

    std::vector<Move> _white_moves;
    std::vector<Move> _black_moves;

    std::shared_ptr<GraphicsObserver> _graphics_observer;
    std::shared_ptr<TextObserver> _text_observer;

    void performMove(Move move, Color player_color);

   public:
    Game();
    std::shared_ptr<Player> createPlayerPtr(PlayerType::Type type, Color color, std::weak_ptr<Game> game);
    void setupPlayers(PlayerType::Type white, PlayerType::Type black, std::weak_ptr<Game> game);
    void setupBoard();
    void initDefaultGame();
    bool anyValidMoves(Color player_color);
    bool makeTurn(Move move, Color color, bool in_check);
    SimulateMoveInfo simulateMove(Move move, Color player_color);
    void reverseMoves(int n);
    void peek(Position pos, Color player_color);

    void renderBoard() const;

    Move getLastMove(Color player_color) const;

    Player& getWhite() const;
    Player& getBlack() const;
    ChessBoard& getChessBoard() const;

    ~Game() = default;
};

#endif