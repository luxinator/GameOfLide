//
// Created by lucas on 7/14/15.
//

#ifndef GAMEOFLIDE_SDL2_GAMEBOARD_H
#define GAMEOFLIDE_SDL2_GAMEBOARD_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>


class GameBoard {

    const size_t Nx, Ny;
    int tileWidth, tileHeight;
    SDL_Rect ***tiles;
    char **states;
    char **futureState;

    bool Grid;

    int nrOfLiveNeighbors(size_t i, size_t j);


public:

    GameBoard(size_t Ny, size_t Nx, int tileWidth, int tileHeight);

    void setPatern();

    void cleanBoard();

    void killCell(int x, int y);

    void populateCell(int x, int y);

    void showGrid();

    void drawBoard(SDL_Renderer *ren);

    void tick();

    ~GameBoard();

};


#endif //GAMEOFLIDE_SDL2_GAMEBOARD_H
