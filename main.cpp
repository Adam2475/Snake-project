#include <iostream>
#include "SDL3/SDL.h"
#include "entity.hpp"
#include "struct.hpp"
#include "./player/player.hpp"
#include "./collectables/collectables.hpp"
// #include "SDL3/SDL_ttf.h"

bool checkBorderCollision(Player *player, int screenW, int screenH)
{
    int x = player->getPosX();
    int y = player->getPosY();

    // assuming snake head is 10x10
    if (x < 0 || y < 0 || x + 10 > screenW || y + 10 > screenH) {
        return true;
    }
    return false;
}

void renderPlayer(Player **player, SDL_Renderer **renderer)
{
    e_direction dir = (*player)->getDirection();
    // Clear screen to black
    SDL_SetRenderDrawColor((*renderer), 0, 0, 0, 255);
    SDL_RenderClear((*renderer));
    SDL_SetRenderDrawColor((*renderer), 255, 0, 0, 255);

    // draw head
    SDL_FRect playerRect = { (float)(*player)->getPosX(), (float)(*player)->getPosY(), 10, 10 };
    SDL_RenderFillRect(*renderer, &playerRect);
    //int i = 0;
    // while (i <= (*player)->getSize())
    // {
    //     t_position pos = (*player)->getPrevPosition()[i];
    //     SDL_FRect bodyRect = { (float)pos.x, (float)pos.y, 10, 10 };
    //     SDL_RenderFillRect(*renderer, &bodyRect);
    //     i++;
    // }
    for (int i = 0; i < (*player)->getPrevPosition().size(); i++) {
        t_position pos = (*player)->getPrevPosition()[i];
        SDL_FRect bodyRect = { (float)pos.x, (float)pos.y, 10, 10 };
        SDL_RenderFillRect(*renderer, &bodyRect);
    }
    //i = 0;
}

int main()
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    t_gamestate *gamestate;
    
    gamestate = new t_gamestate;
    gamestate->is_running = true;
    gamestate->speed = 8;
    gamestate->collected_food = 0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayID display = SDL_GetPrimaryDisplay();
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(display, &display_bounds);
    srand((unsigned int)time(nullptr));
    
     int width = display_bounds.w;
     int heigth = display_bounds.h;
     Player *player = new Player(width / 2, heigth / 2);
     player->setSize(4);
     int j = 0;
     while (j < player->getSize())
     {
          t_position pos{player->getPosX() + (j * 10), player->getPosY()};
          player->addPosition(pos);
          j++;
     }

     player->setDirection(LEFT);
     SDL_CreateWindowAndRenderer("Snake", width, heigth * 0.95, 0, &window, &renderer);

     while(gamestate->is_running)
     {
         handleInput(&gamestate, &player);
         renderPlayer(&player, &renderer);
        //  spawnCollectable(&renderer, &gamestate);

        spawnCollectable(&renderer, gamestate, width, heigth * 0.95);
        checkCollect(player, gamestate);
         // costantly move the player
         move_player(&player, *gamestate);

             
         if (checkBorderCollision(player, width, heigth * 0.95)) {
            gamestate->is_running = false;  // stop game
            std::cout << "Game Over: hit border!\n";
        }
         // Present the frame
         SDL_RenderPresent(renderer);
     }
     delete(player);
    delete(gamestate);
    //free(gamestate);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;    
}