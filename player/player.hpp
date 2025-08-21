#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "../struct.hpp"
#include "../entity.hpp"
#include <vector>

enum e_direction
{
    UP,
    LEFT,
    RIGHT,
    DOWN
};

class Player : public entity
{
    private:
        int size;
        e_direction dir;
        std::vector<t_position> prev_pos;   // dynamic array
    public:
        Player(int x, int y);
        ~Player();
        
        void setDirection(const e_direction x);
        e_direction getDirection() const;

        void setPrevPosition(const std::vector<t_position> x);
        std::vector<t_position> &getPrevPosition();
        const std::vector<t_position> &getPrevPosition() const;
        
        void addPosition(t_position pos);

        void setSize(const int x);
        int getSize() const;
};


void move_player(Player **player, t_gamestate gamestate);
void handleInput(t_gamestate **gamestate, Player **player);

#endif