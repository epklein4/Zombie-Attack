#ifndef PATHFINDER_H
#define PATHFINDER_H


#include "Tile.h"

#include <vector>
#include <SDL2/SDL.h>

#define GOAL 0
#define NOT_PATHABLE -1
#define UNPATHED -2

class Pathfinder {
    public:
        Pathfinder();
        Pathfinder(int rows, int cols, std::vector<Tile>* tiles);
        ~Pathfinder();

        void createPathfinder(int rows, int cols, std::vector<Tile>* tiles);

        void setGoal(int x, int y);
        SDL_Point getPath(int x, int y);

    private:
        int** pathDist;
        bool** visited;
        SDL_Point** paths;
        SDL_Point tileDimensions;
        int rows;
        int cols;

        int goalRow;
        int goalCol;

        void calculatePathField();
        void BTS(int row, int col, int value);
};


#endif