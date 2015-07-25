#include <iostream>
#include <SDL2/SDL.h>

#include "GameBoard.h"

const int SCREEN_WIDTH = 1024; const int SCREEN_HEIGHT = 1024;
const int nrOfTilesX = 100, nrOfTilesY = 100;
const Uint32 REFRESH_RATE = 100;
bool quit;

int main() {

    SDL_Window *window;
    SDL_Surface *screensurface;
    quit = false;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize!\n SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("GameOfLife", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        std::cout << "SDL could not initialize!\n SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    GameBoard *g = new GameBoard(nrOfTilesX,nrOfTilesY, SCREEN_WIDTH / nrOfTilesX, SCREEN_HEIGHT/nrOfTilesY);

    // Enter Game Loop Here is Where the Magic Happens
    SDL_Event event;

    Uint32  timer = 0;
    Uint32 timeToRefresh;

    int mouseX, mouseY;
    bool mouseLeftDown = false;
    bool mouseRightDown = false;

    bool pause = true;
    bool step = false;
    while(!quit){

        //Events
        while( SDL_PollEvent(&event) != 0) {

            if (event.type == SDL_QUIT)
                quit = true;
            else if (event.type == SDL_KEYDOWN) {

                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;

                    case SDLK_SPACE:
                        if (pause)
                            pause = false;
                        else
                            pause = true;
                        break;

                    case SDLK_t:
                        if (step)
                            step = false;
                        else
                            step = true;
                        break;

                    case SDLK_r:
                        g->cleanBoard();
                        g->setPatern();
                        break;

                    case SDLK_c:
                        g->cleanBoard();
                        break;

                    case SDLK_g:
                        g->showGrid();

                    default:
                        break;
                }
            }
            // Mouse input
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouseLeftDown = true;
                if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseRightDown = true;
            } else if (event.type == SDL_MOUSEBUTTONUP ){
                if(event.button.button == SDL_BUTTON_LEFT)
                    mouseLeftDown = false;
                if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseRightDown = false;
            }
        }

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        if( !pause && SDL_GetTicks() - timer > REFRESH_RATE) {
            //std::cout << "TICK" << std::endl;
            g->tick();
            timeToRefresh = timer - SDL_GetTicks();
            timer = SDL_GetTicks();
        } else if (pause && step){
            std::cout << "USER TICK" << std::endl;
            g->tick();
            step = false;
        }

        //Mouse Input Handler
        if(mouseLeftDown){
            SDL_GetMouseState(&mouseX, &mouseY);
            g->populateCell(mouseX, mouseY);
        }
        if(mouseRightDown){
            SDL_GetMouseState(&mouseX, &mouseY);
            g->killCell(mouseX, mouseY);
        }

        g->drawBoard(renderer);
        SDL_RenderCopy(renderer, NULL, NULL, NULL);

        SDL_RenderPresent(renderer);

    }


    delete g;
    std::cout << "Cleaning up!" << std::endl;
    SDL_DestroyWindow(window);

    SDL_Quit();

    std::cout << "Quiting" << std::endl;
    return 0;
}