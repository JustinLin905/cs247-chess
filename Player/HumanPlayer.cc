#include "HumanPlayer.h"

#include "../CommandInterpreter/CommandInterpreter.h"

HumanPlayer::HumanPlayer(Color color, Game& game) : Player(color, game) {}

Move HumanPlayer::getMove() {
    CommandInterpreter::processPlayerInput(_game, *this);
}