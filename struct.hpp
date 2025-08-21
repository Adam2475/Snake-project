#pragma once
#include "SDL3/SDL.h"

typedef struct s_position
{
    int x;
    int y;
} t_position;

typedef struct s_gamestate
{
    bool is_running;
    int speed;
    int collected_food;

    SDL_FRect collectable;   // position & size of current collectable
    bool has_collectable;    // whether one is active
} t_gamestate;
