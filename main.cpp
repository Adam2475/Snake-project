#include <iostream>
#include "SDL3/SDL.h"
#include "entity.hpp"
#include "struct.hpp"
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
    int i = 0;
    while (i <= (*player)->getSize())
    {
        t_position pos = (*player)->getPrevPosition()[i];
        // if (dir == UP || dir == DOWN)
        // {
        //     SDL_FRect playerRect = { (float)(*player)->getPosX(), (float)(*player)->getPosY() + (i * 10), 10, 10 };
        //     SDL_RenderFillRect((*renderer), &playerRect);
        // }
        // else if (dir == LEFT || dir == RIGHT)
        // {
        //     SDL_FRect playerRect = { (float)(*player)->getPosX() + (i * 10), (float)(*player)->getPosY(), 10, 10 };
        //     SDL_RenderFillRect((*renderer), &playerRect);
        // }
        SDL_FRect bodyRect = { (float)pos.x, (float)pos.y, 10, 10 };
        SDL_RenderFillRect(*renderer, &bodyRect);
        i++;
    }
    i = 0;
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

int main()
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    t_gamestate *gamestate;
    
    gamestate = (t_gamestate *)malloc(sizeof(t_gamestate *) * 1);
    gamestate->is_running = true;
    gamestate->speed = 8;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayID display = SDL_GetPrimaryDisplay();
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(display, &display_bounds);
    
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

    // for (const auto& pos : player->getPrevPosition()) {
    //     std::cout << "(" << pos.x << ", " << pos.y << ") ";
    // }
    // std::cout << std::endl;

    // return 0;

    // player->prev_pos 
    player->setDirection(LEFT);
    
    SDL_CreateWindowAndRenderer("Snake", width, heigth * 0.95, 0, &window, &renderer);
    SDL_GetWindowSizeInPixels(window, &width, &heigth);

    // std::cout << "width" << width << "heigth" << heigth << std::endl;

    while(gamestate->is_running)
    {
        handleInput(&gamestate, &player);
        renderPlayer(&player, &renderer);
        // costantly move the player
        move_player(&player, *gamestate);
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