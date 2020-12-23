#ifndef MAPREADER_H
#define MAPREADER_H

#include <fstream>
#include <string>
#include <vector>

#include "Tile.h"

const int WALL  = 1;
const int SPACE = 0;

class MapReader {
    public:
        MapReader();
        ~MapReader();
        
        void init(std::string mapname, int windowWidth, int windowHeight);

        void generateMap();

        void generateTiles();

        void resize(int windowWidth, int windowHeight);

        SDL_Point getDimensions();
        SDL_Point getTileDimensions();
        std::vector<Tile>* getTiles();

    private:
        std::ifstream mapfile;
        std::vector<Tile> tiles;
        int** map;
        int rows;
        int cols;
        int tileWidth;
        int tileHeight;
};

#endif