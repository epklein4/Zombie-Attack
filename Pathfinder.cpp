#include "Pathfinder.h"
#include <queue>

Pathfinder::Pathfinder() {}

/*
 *  Creates a pathfinder with rows, cols, and a list of tiles in the level
 */
Pathfinder::Pathfinder(int rows, int cols, std::vector<Tile>* tiles) {
    createPathfinder(rows, cols, tiles);
}

Pathfinder::~Pathfinder() {}

/*
 *  Method for initializing a pathfinder given rows, cols, and a list of tiles in the level
 */
void Pathfinder::createPathfinder(int rows, int cols, std::vector<Tile>* tiles) {
    this->rows = rows;
    this->cols = cols;
    tileDimensions = tiles->front().getDimensions();
    pathDist = new int*[rows];
    visited = new bool*[rows];
    paths = new SDL_Point*[rows];
    
    for(int i = 0; i < rows; i++) {
        pathDist[i] = new int[cols];
        visited[i] = new bool[cols];
        paths[i] = new SDL_Point[cols];
        for(int j = 0; j < cols; j++) {
            pathDist[i][j] = UNPATHED;
            paths[i][j] = {0, 0};
            BoundingBox currBounds;
            currBounds.updateBoundingBox(j * tileDimensions.x + 1,
                                         i * tileDimensions.y + 1,
                                         tileDimensions.x - 2,
                                         tileDimensions.y - 2);
            for(Tile &tile : *tiles) {
                tile.updateBoundingBox();
                if(tile.getBoundingBox().checkCollision(currBounds)) {
                    pathDist[i][j] = NOT_PATHABLE;
                }
            }
        }
    }
}

/*
 *  Checks if the goal has moved(the goal being the position of the player),
 *  and if it has creates an array of pathable positions and using a Breath-First Search
 *  creates paths to the goal from the pathable position on the map.
 */
void Pathfinder::setGoal(int x, int y) {
    int oldCol = goalCol;
    int oldRow = goalRow;
    goalCol = x / tileDimensions.x;
    goalRow = y / tileDimensions.y;

    if(oldCol != goalCol || oldRow != goalRow) {

        //clear previous dist values
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                visited[i][j] = false;
                if(pathDist[i][j] != NOT_PATHABLE) { pathDist[i][j] = UNPATHED; }
            }
        }

        pathDist[goalRow][goalCol] = GOAL;
        BTS(goalRow, goalCol, pathDist[goalRow][goalCol]);
        calculatePathField();
    }
}

/*
 *  Gets the path from a given position to the goal using the paths 2d array
 */
SDL_Point Pathfinder::getPath(int x, int y) {
    int col = x / tileDimensions.x;
    int row = y / tileDimensions.y;
    if(col < 0 || row < 0 || row >= rows || col >= cols) { return {0, 0}; }
    return paths[row][col];
}

/*
 *  updates the field of path vectors to the goal
 */
void Pathfinder::calculatePathField() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            int current = pathDist[i][j];
            int up = NOT_PATHABLE;
            int down = NOT_PATHABLE;
            int left = NOT_PATHABLE;
            int right = NOT_PATHABLE;
            if(i != 0) { up = pathDist[i-1][j]; }
            if(i != rows - 1) { down = pathDist[i+1][j]; }
            if(j != 0) { left = pathDist[i][j-1]; }
            if(j != cols - 1) { right = pathDist[i][j+1]; }
            if(current == NOT_PATHABLE) { continue; }
            if(up == NOT_PATHABLE) { up = current; }
            if(down == NOT_PATHABLE) { down = current; }
            if(left == NOT_PATHABLE) { left = current; }
            if(right == NOT_PATHABLE) { right = current; }
            paths[i][j].x = left - right;
            paths[i][j].y = up - down;
        }
    }
}

/*
 *  Uses a Breadth-First Search to find the the distance from every pathable tile to
 *  the goal(player).
 * 
 *  For further information of a Breadth-First Search:
 *  (https://en.wikipedia.org/wiki/Breadth-first_search)
 */
void Pathfinder::BTS(int row, int col, int value) {
    visited[row][col] = true;
    std::queue<SDL_Rect> queue;

    SDL_Rect currentPath = {row, col, value, 0};
    queue.push(currentPath);
    
    while(!queue.empty()) {
        currentPath = queue.front();
        row = currentPath.x;
        col = currentPath.y;
        value = currentPath.w;
        queue.pop();

        if(row != 0) { //row-1
            if(!visited[row-1][col]) {
                visited[row-1][col] = true;
                if(pathDist[row-1][col] != NOT_PATHABLE) {
                    pathDist[row-1][col] = value + 1;
                    queue.push({row-1, col, value + 1, 0});
                }
            }
        }
        if(row != rows - 1) { //row+1
            if(!visited[row+1][col]) {
                visited[row+1][col] = true;
                if(pathDist[row+1][col] != NOT_PATHABLE) {
                    pathDist[row+1][col] = value + 1;
                    queue.push({row+1, col, value + 1, 0});
                }
            }
        }
        if(col != 0) { //col-1
            if(!visited[row][col-1]) {
                visited[row][col-1] = true;
                if(pathDist[row][col-1] != NOT_PATHABLE) {
                    pathDist[row][col-1] = value + 1;
                    queue.push({row, col-1, value + 1, 0});
                }
            }
        }
        if(col != cols - 1) { //col+1
            if(!visited[row][col+1]) {
                visited[row][col+1] = true;
                if(pathDist[row][col+1] != NOT_PATHABLE) {
                    pathDist[row][col+1] = value + 1;
                    queue.push({row, col+1, value + 1, 0});
                }
            }
        }
    }
    
    return;
}