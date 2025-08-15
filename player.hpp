#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "struct.hpp"
#include "entity.hpp"

class Player : public entity
{
    protected:
        int size;
    public:
       Player(int x, int y);
       ~Player();
};

#endif