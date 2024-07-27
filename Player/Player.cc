#include "Player.h"

#include "../Game/Game.h"
#include "../Manager/Manager.h"
#include "../Piece/Piece.h"

Player::Player(Color color, std::shared_ptr<Game> game) : _color(color), _game{game} {}

void Player::resign() {
    Manager::closeGame();
}