#include "HumanPlayer.h"

#include "../CommandInterpreter/CommandInterpreter.h"

HumanPlayer::HumanPlayer(Color color) : Player(color) {}

Move HumanPlayer::getMove() {
    return CommandInterpreter::processPlayerInput(*this);
}