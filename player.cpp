#include "player.hpp"

// parameter injection from entity constructor
Player::Player(int x, int y) : entity(x, y)
{
    this->size = 0;
}

Player::~Player()
{

}