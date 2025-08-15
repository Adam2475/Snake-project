#include "entity.hpp"        

entity::entity(int x, int y)
{
    this->pos.x = x;
    this->pos.y = y; 
}
        
entity::entity(const entity &src)
{
    this->pos.x = src.pos.x;
    this->pos.y = src.pos.y; 
}


entity::~entity() {}


entity &entity::operator=(const entity &src)
{
    if (this != &src)
    {
        this->pos.x = src.pos.x;
        this->pos.y = src.pos.y; 
    }
    return *this;
}

int entity::getPosY() const
{
    return this->pos.y;
}

int entity::getPosX() const
{
    return this->pos.x;
}

void entity::setPosY(int newPos)
{
    this->pos.y = newPos;
}

void entity::setPosX(int newPos)
{
    this->pos.x = newPos;
}