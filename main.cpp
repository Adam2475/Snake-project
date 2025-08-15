#include <iostream>
#include "SDL3/SDL.h"
#include "entity.hpp"
#include "struct.hpp"
#include "player.hpp"

void renderEntity(Player **player, SDL_Renderer **renderer)
{
    // Clear screen to black
    SDL_SetRenderDrawColor((*renderer), 0, 0, 0, 255);
    SDL_RenderClear((*renderer));
    // Draw a red square at (square_x, square_y)
    SDL_FRect playerRect = { (float)(*player)->getPosX(), (float)(*player)->getPosY(), 10, 10 };
    SDL_SetRenderDrawColor((*renderer), 255, 0, 0, 255); // red
    SDL_RenderFillRect((*renderer), &playerRect);
}

void handleInput(t_gamestate **gamestate, Player **player)
{
    int x = (*player)->getPosX();
    int y = (*player)->getPosY();
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        // if( event.type == SDL_EVENT_MOUSE_MOTION )
        // {
        //     mx = event.motion.x;
        //     my = event.motion.y;
        // }
        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.key == SDLK_ESCAPE)
                (*gamestate)->is_running = false;

            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                switch (event.key.key)
                {
                    case SDLK_W:
                        std::cout << "Move up (W)\n";
                        std::cout << "x" << x << std::endl;
                        (*player)->setPosY(y - 2);
                        break;
                    case SDLK_A:
                        std::cout << "Move left (A)\n";
                        (*player)->setPosX(x - 2);
                        break;
                    case SDLK_S:
                        std::cout << "Move down (S)\n";
                        (*player)->setPosY(y + 2);
                        break;
                    case SDLK_D:
                        std::cout << "Move right (D)\n";
                        (*player)->setPosX(x + 2);
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

int main()
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    t_gamestate *gamestate;
    
    gamestate = (t_gamestate *)malloc(sizeof(t_gamestate *) * 1);
    gamestate->is_running = true;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayID display = SDL_GetPrimaryDisplay();
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(display, &display_bounds);
    
    int width = display_bounds.w;
    int heigth = display_bounds.h;
    Player *player = new Player(width / 2, heigth / 2);
    
    SDL_CreateWindowAndRenderer("Snake", width, heigth * 0.95, 0, &window, &renderer);
    SDL_GetWindowSizeInPixels(window, &width, &heigth);

    // float mx = 0;
    // float my = 0;

    std::cout << "width" << width << "heigth" << heigth << std::endl;

    while(gamestate->is_running)
    {
        handleInput(&gamestate, &player);
        renderEntity(&player, &renderer);
        // Present the frame
        SDL_RenderPresent(renderer);
    }

    delete(player);
    free(gamestate);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;    
}