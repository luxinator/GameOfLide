//
// Created by lucas on 7/14/15.
//

#include <iostream>
#include "GameBoard.h"



GameBoard::GameBoard(size_t Ny, size_t Nx, int tileWidth, int tileHeight) : Nx(Ny), Ny(Nx), tileWidth(tileWidth), tileHeight(tileHeight) {


    this->Grid = true;
    char *tStates = new char[Nx * Ny];
    char *tfStates = new char[Nx * Ny];
    this->states = new char *[Ny];
    this->futureState = new char *[Ny];

    SDL_Rect **tTiles = new SDL_Rect*[Nx * Ny];
    this->tiles = new SDL_Rect **[Ny];


//    std::cout << "Creating Tiles on Board at: " << this << std::endl;
//    std::cout << "x\ty\tw\th\tstate" << std::endl;

    for (size_t i = 0; i < Ny; i++) {
        this->states[i] = tStates + i * Ny;
        this->futureState[i] = tfStates + i * Ny;

        this->tiles[i] = tTiles + i * Ny;

        for (size_t j = 0; j < Nx; j++) {
            this->states[i][j] = (char) 0;
            this->futureState[i][j] = (char) 0;

            this->tiles[i][j] = new SDL_Rect;
            this->tiles[i][j]->x = (int) i * tileWidth;
            this->tiles[i][j]->y = (int) j * tileHeight;

            this->tiles[i][j]->h = tileHeight;
            this->tiles[i][j]->w = tileWidth;
//            std::cout << this->tiles[i][j]->x << '\t' << this->tiles[i][j]->y << '\t';
//            std::cout << this->tiles[i][j]->w << '\t' << this->tiles[i][j]->h << '\t' << (int)this->states[i][j] << std::endl;
        }
    }
}

void GameBoard::showGrid() {
    if (this->Grid)
        this->Grid = false;
    else
        this->Grid = true;
}

void GameBoard::setPatern() {

//    for (size_t i = 0; i < this->Nx; i++)
//        for (size_t j = 0; j < this->Ny; j++) {
//            if (i + j % 2 == 0) {
//                this->states[i][j] = (char) 1;
//                this->futureState[i][j] = (char) 1;
//            }
//        }


    //R-pentonino
    this->states[50][50] = (char) 1;
    this->states[51][50] = (char) 1;
    this->states[50][51] = (char) 1;
    this->states[50][52] = (char) 1;
    this->states[49][51] = (char) 1;

    //Glider
    this->states[75][75] = (char) 1;
    this->states[75][76] = (char) 1;
    this->states[75][77] = (char) 1;
    this->states[74][77] = (char) 1;
    this->states[73][76] = (char) 1;

    //beacon
    this->states[25][25] = (char) 1;
    this->states[26][25] = (char) 1;
    this->states[25][26] = (char) 1;

    this->states[27][28] = (char) 1;
    this->states[28][28] = (char) 1;
    this->states[28][27] = (char) 1;

    //Toad
    this->states[33][25] = (char) 1;
    this->states[34][25] = (char) 1;
    this->states[35][25] = (char) 1;
    this->states[32][24] = (char) 1;
    this->states[33][24] = (char) 1;
    this->states[34][24] = (char) 1;

    //block
    this->states[60][60] = (char) 1;
    this->states[60][61] = (char) 1;
    this->states[61][61] = (char) 1;
    this->states[61][60] = (char) 1;

}

void GameBoard::drawBoard(SDL_Renderer * ren) {

    // There is a SDL_FillRects() this fills a set of rects, test if it is faster then individual like this
    //std::cout << "Drawing Tiles" << std::endl;

    for (size_t i = 0; i < Nx; i++) {
        for (size_t j = 0; j < Ny ; j++) {
            if (this->states[i][j] == (char) 1)
                SDL_SetRenderDrawColor(ren, 0,0,255,255);
            else if (this->states[i][j] == (char) 0)
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            else if (this->states[i][j] == 'a')
                SDL_SetRenderDrawColor(ren, 255, 0, 255, 255);


            if(SDL_RenderFillRect(ren, this->tiles[i][j]) != 0){
                std::cout << "Rectangle: " << i << '\t' << j << " failed!" << std::endl;
            }
        }
    }
    //Draw Grid Lines
    if(this->Grid){
        SDL_SetRenderDrawColor(ren, 127, 127, 127, 75);

        for(size_t i = 1; i < Nx; i++){
            SDL_RenderDrawLine(ren, i * this->tileWidth, 0,
                                    i * this->tileWidth, Ny*tileWidth);
        }
        for(size_t j = 1; j < Ny; j++){
            SDL_RenderDrawLine(ren, 0, j * this->tileHeight,
                               this->tileWidth *Nx, this->tileHeight * j);
        }

    }
}

void GameBoard::cleanBoard() {
    for (size_t i = 1; i < Nx - 1; i++) {
        for (size_t j = 1; j < Ny - 1; j++) {
            this->states[i][j] = (char) 0;
            this->futureState[i][j] = (char) 0;
        }
    }
}

int GameBoard::nrOfLiveNeighbors(size_t i, size_t j) {
    int LiveNeighbors = 0;

    //Row Above Cell
    if (this->states[i - 1][j - 1] == (char) 1)
        LiveNeighbors++;
    if (this->states[i]    [j - 1] == (char) 1)
        LiveNeighbors++;
    if (this->states[i + 1][j - 1] == (char) 1)
        LiveNeighbors++;

    //Row Beneath Cell
    if (this->states[i - 1][j + 1] == (char) 1)
        LiveNeighbors++;
    if (this->states[i]    [j + 1] == (char) 1)
        LiveNeighbors++;
    if (this->states[i + 1][j + 1] == (char) 1)
        LiveNeighbors++;

    //Left and Right
    if (this->states[i + 1][j] == (char) 1)
        LiveNeighbors++;
    if (this->states[i - 1][j] == (char) 1)
        LiveNeighbors++;

    return LiveNeighbors;
}

void GameBoard::tick() {


    for (size_t i = 1; i < Nx- 1 ; i++) {
        for (size_t j = 1; j < Ny - 1 ; j++) {
            int myNeighbours = nrOfLiveNeighbors(i, j);
            //Live Cell
            if (this->states[i][j] == (char) 1) {
                if(myNeighbours < 2)
                    this->futureState[i][j] = (char) 0;
                else if(myNeighbours == 2 || myNeighbours == 3)
                    this->futureState[i][j] = (char) 1;
                else if(myNeighbours > 3)
                    this->futureState[i][j] = 'a';
                else
                    std::cout << "IMPOSIBRU!!!" <<std::endl;
            } //Dead Cell
            else if (myNeighbours == 3)
                this->futureState[i][j] = (char) 1;
        }
    }
    //Swap
    char **t = this->states;
    this->states = this->futureState;
    this->futureState = t;
    for (size_t i = 1; i < Nx- 1 ; i++) {
        for (size_t j = 1; j < Ny - 1; j++) {
            this->futureState[i][j] = (char) 0;
        }
    }


}

void GameBoard::killCell(int x, int y) {
    size_t i = x / this->tileWidth;
    size_t j = y / this->tileHeight;
    if(i < Nx && j < Ny)
        this->states[i][j] = (char) 0;
}

void GameBoard::populateCell(int x, int y) {
    size_t i = x / this->tileWidth;
    size_t j = y / this->tileHeight;
    if(i < Nx && j < Ny)
        this->states[i][j] = (char) 1;
}

GameBoard::~GameBoard(){
    for (size_t i = 1; i < Nx- 1 ; i++) {
        for (size_t j = 1; j < Ny - 1 ; j++) {
            delete this->tiles[i][j];
            }
        }

    delete[] this->tiles;
    delete[] this->states, this->futureState;

}