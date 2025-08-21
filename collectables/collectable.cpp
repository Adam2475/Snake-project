#include <cstdlib>
#include <ctime>
#include "collectables.hpp"

void spawnCollectable(SDL_Renderer **renderer, t_gamestate *gamestate, int screenW, int screenH)
{
    if (!gamestate->has_collectable)
    {
        // Random position on grid (10x10 tiles like the snake)
        int x = (rand() % (screenW / 10)) * 10;
        int y = (rand() % (screenH / 10)) * 10;

        gamestate->collectable = { (float)x, (float)y, 10, 10 };
        gamestate->has_collectable = true;
    }

    // Draw it
    SDL_SetRenderDrawColor(*renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(*renderer, &gamestate->collectable);
}

void checkCollect(Player *player, t_gamestate *gamestate)
{
    SDL_FRect playerHead = { (float)player->getPosX(), (float)player->getPosY(), 10, 10 };

    if (SDL_HasRectIntersectionFloat(&playerHead, &gamestate->collectable)) {
        gamestate->collected_food++;
        gamestate->has_collectable = false;

        // grow snake: add one more segment at tail
        if (!player->getPrevPosition().empty()) {
            t_position lastPos = player->getPrevPosition().back();
            player->addPosition(lastPos);
        } else {
            // if no body yet, add head position
            t_position pos{player->getPosX(), player->getPosY()};
            player->addPosition(pos);
        }

        player->setSize(player->getSize() + 1);
    }
}