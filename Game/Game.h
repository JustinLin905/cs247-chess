#ifndef GAME_H
#define GAME_H

#include <memory>

#include "../ChessBoard/ChessBoard.h"
#include "../Move/Move.h"
#include "../ObserverPattern/GraphicsObserver.h"
#include "../ObserverPattern/TextObserver.h"
#include "../Player/Player.h"
#include "../PlayerType/PlayerType.h"

class Game {
    std::shared_ptr<ChessBoard> _chess_board;
    std::unique_ptr<Player> _white;
    std::unique_ptr<Player> _black;

    std::shared_ptr<GraphicsObserver> _graphics_observer;
    std::shared_ptr<TextObserver> _text_observer;

    void performMove(Move move, Color player_color);

   public:
    Game();
    std::unique_ptr<Player> createPlayerPtr(PlayerType::Type type);
    void setupPlayers(PlayerType::Type white, PlayerType::Type black);
    void initDefaultGame();
    bool anyValidMoves(Color player_color);
    bool makeTurn(Move move, Color color, bool in_check);
    bool simulateLegality(Move move, Color player_color);
    void reverseMoves(int n);

    void renderBoard() const;

    Player& getWhite() const;
    Player& getBlack() const;

    ~Game() = default;
};

#endif