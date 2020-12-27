#ifndef PATHFINDER_H
#define PATHFINDER_H


#include "Tile.h"

#include <vector>
#include <SDL2/SDL.h>

#define NOT_PATHABLE -1
#define UNPATHED 0

class Pathfinder {
    public:
        Pathfinder();
        Pathfinder(int rows, int cols, std::vector<Tile>* tiles);
        ~Pathfinder();

        void createPathfinder(int rows, int cols, std::vector<Tile>* tiles);

        void setGoal(int x, int y);
        SDL_Point getPath(int x, int y);

    private:
        int** pathable;
        SDL_Point** paths;
        SDL_Point tileDimensions;

        int goalRow;
        int goalCol;


};


#endif