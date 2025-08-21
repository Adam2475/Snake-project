#pragma once

#include "SDL3/SDL.h"   // for SDL_Renderer, SDL_FRect
#include "../struct.hpp"  // for t_gamestate
#include "../player/player.hpp"  // for Player

void spawnCollectable(SDL_Renderer **renderer, t_gamestate *gamestate, int screenW, int screenH);
void checkCollect(Player *player, t_gamestate *gamestate);
