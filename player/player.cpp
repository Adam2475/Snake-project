#include "player.hpp"

// parameter injection from entity constructor
Player::Player(int x, int y) : entity(x, y)
{
    this->size = 0;
}

Player::~Player()
{

}

e_direction Player::getDirection() const
{
    return this->dir;
}

void Player::setDirection(const e_direction x)
{
    this->dir = x;
}

void Player::setSize(const int x)
{
    this->size = x;
}

int Player::getSize() const 
{
    return this->size;
}

void Player::setPrevPosition(const std::vector<t_position> x)
{
    this->prev_pos = x;
}

std::vector<t_position> &Player::getPrevPosition()
{   
    return this->prev_pos;
}

const std::vector<t_position> &Player::getPrevPosition() const
{   
    return this->prev_pos;
}

void Player::addPosition(t_position pos)
{
    this->prev_pos.push_back(pos); 
}