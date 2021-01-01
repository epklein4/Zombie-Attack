#include "MapReader.h"
#include <sstream>
#include <string>

MapReader::MapReader() {}

/*
 * Close the tile map file
 * Delete the map from memory
 */
MapReader::~MapReader() {
    this->mapfile.close();
    for(int i = rows - 1; i >= 0; i--) {
        delete map[i];
    }
    delete map;
}

/*
 *  Initialize the map reader with the tilemap files name and the windows width and height
 * 
 *  Generates the map and tile list for the map
 */
void MapReader::init(std::string mapname, int windowWidth, int windowHeight) {
    this->mapfile.open(mapname);
    std::string line;
    std::stringstream linestream;

    //rows in map
    std::getline(mapfile, line);
    linestream << line;
    linestream >> this->rows;
    linestream.clear();

    //cols in map
    std::getline(mapfile, line);
    linestream << line;
    linestream >> this->cols;
    linestream.clear();
    
    resize(windowWidth, windowHeight);

    printf("Rows: %d    Cols: %d\n", rows, cols);
    generateMap();
    generateTiles();
}

/*
 *  Generates the map from each line of the tilemap file
 */
void MapReader::generateMap() {
    std::string line;

    map = new int*[rows];
    for(int i = 0; i < rows; i++) {
        map[i] = new int[cols];
        std::getline(mapfile, line);
        for(int j = 0; j < cols; j++) {
            switch(line[j]) {
                case 'x': map[i][j] = WALL; printf("x"); break;
                case 'o': map[i][j] = SPACE; printf("o"); break;
            }
        }
        printf("\n");
    }
}

/*
 *  Generates the tiles from the map 2d array
 */
void MapReader::generateTiles() {
    tiles.reserve(rows * cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(map[i][j] == WALL) {
                Tile tile(nullptr,
                          j * tileWidth,
                          i * tileHeight,
                          tileWidth,
                          tileHeight);
                tiles.push_back(tile);
            }
        }
    }
}

/*
 *  Resizes the tiles to match the new dimensions of the their display window
 */
void MapReader::resize(int windowWidth, int windowHeight) {
    int oldTileWidth = this->tileWidth;
    int oldTileHeight = this->tileHeight;
    this->tileWidth = windowWidth / this->cols;
    this->tileHeight = windowHeight / this->rows;
    for (Tile &tile: tiles) {
        tile.setPosition(((double)tile.getPosition().x / oldTileWidth) * tileWidth, 
                         ((double)tile.getPosition().y / oldTileHeight) * tileHeight);
        
        tile.setWidth((double)windowWidth / cols);
        tile.setHeight((double)windowHeight / rows);  
    }
}

/*
 *  Gets the rows and cols of the map
 */
SDL_Point MapReader::getDimensions() {
    SDL_Point dimensions = {rows, cols};
    return dimensions;
}

/*
 *  Gets the dimensions of the tiles of the map
 */
SDL_Point MapReader::getTileDimensions() {
    SDL_Point tileDimensions = {tileWidth, tileHeight};
    return tileDimensions;
}

/*
 *  Gets the list of tiles in the map
 */
std::vector<Tile>* MapReader::getTiles() {
    return &tiles;
}