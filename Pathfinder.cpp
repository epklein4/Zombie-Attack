#include "Pathfinder.h"

#include <cstdio>
Pathfinder::Pathfinder() {}

Pathfinder::Pathfinder(int rows, int cols, std::vector<Tile>* tiles) {
    createPathfinder(rows, cols, tiles);
}

Pathfinder::~Pathfinder() {}

void Pathfinder::createPathfinder(int rows, int cols, std::vector<Tile>* tiles) {
    tileDimensions = tiles->front().getDimensions();
    pathable = new int*[rows];
    paths = new SDL_Point*[rows];
    
    for(int i = 0; i < rows; i++) {
        pathable[i] = new int[cols];
        paths[i] = new SDL_Point[cols];
        for(int j = 0; j < cols; j++) {
            pathable[i][j] = UNPATHED;
            BoundingBox currBounds;
            currBounds.updateBoundingBox(j * tileDimensions.x + 1,
                                         i * tileDimensions.y + 1,
                                         tileDimensions.x - 2,
                                         tileDimensions.y - 2);
            for(Tile &tile : *tiles) {
                tile.updateBoundingBox();
                if(tile.getBoundingBox().checkCollision(currBounds)) {
                    pathable[i][j] = NOT_PATHABLE;
                }
            }
        }
    }
}

void Pathfinder::setGoal(int x, int y) {
    int oldCol = goalCol;
    int oldRow = goalRow;
    goalCol = x / tileDimensions.x;
    goalRow = y / tileDimensions.y;
    if(oldCol != goalCol || oldRow != goalRow) {
        printf("row: %d   col: %d\n", goalRow, goalCol);
    }
}

SDL_Point Pathfinder::getPath(int x, int y) {

    return {-1, -1};
}