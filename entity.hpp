#ifndef ENTITY_HPP
# define ENTITY_HPP

#include "struct.hpp"

class entity
{
    protected:
        t_position pos;
    public:
        entity(int x, int y);
        entity(const entity &src);
        ~entity();
        entity &operator=(const entity &src);

        int getPosY() const;
        int getPosX() const;
        void setPosY(int newPos);
        void setPosX(int newPos);
};

#endif