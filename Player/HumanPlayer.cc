#include "HumanPlayer.h"

#include "../CommandInterpreter/CommandInterpreter.h"

HumanPlayer::HumanPlayer(Color color, std::weak_ptr<Game> game) : Player(color, game) {}

Move HumanPlayer::getMove() {
    return CommandInterpreter::processPlayerInput(*this);
}