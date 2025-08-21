#include <iostream>
#include "SDL3/SDL.h"
#include "../entity.hpp"
#include "../struct.hpp"
#include "player.hpp"

void move_player(Player **player, t_gamestate gamestate)
{
    SDL_Delay(100);

    // Update body positions: shift segments to follow the head
    int size = (*player)->getSize();
    auto &body = (*player)->getPrevPosition();

    // Shift each segment to the previous one's position (start from tail)
    for (int i = size - 1; i > 0; i--) {
        body[i] = body[i - 1];
    }

    // First segment takes head's current position
    if (size > 0) {
        body[0] = { (*player)->getPosX(), (*player)->getPosY() };
    }

    // Move the head
    e_direction dir = (*player)->getDirection();
    if (dir == UP)
        (*player)->setPosY((*player)->getPosY() - gamestate.speed);
    else if (dir == RIGHT)
        (*player)->setPosX((*player)->getPosX() + gamestate.speed);
    else if (dir == LEFT)
        (*player)->setPosX((*player)->getPosX() - gamestate.speed);
    else if (dir == DOWN)
        (*player)->setPosY((*player)->getPosY() + gamestate.speed);
}

void handleInput(t_gamestate **gamestate, Player **player)
{
    int x = (*player)->getPosX();
    int y = (*player)->getPosY();
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.key == SDLK_ESCAPE)
                (*gamestate)->is_running = false;

            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                switch (event.key.key)
                {
                    case SDLK_W:
                        (*player)->setDirection(UP);
                        break;
                    case SDLK_A:
                        (*player)->setDirection(LEFT);
                        break;
                    case SDLK_S:
                        (*player)->setDirection(DOWN);
                        break;
                    case SDLK_D:
                        (*player)->setDirection(RIGHT);
                        break;
                    case SDLK_ESCAPE:
                        (*gamestate)->is_running = false;
                        break;
                }
            }
            if( event.type == SDL_EVENT_QUIT )
            {
                (*gamestate)->is_running = false;
            }
        }
    }
}