#include "MapReader.h"
#include <sstream>
#include <string>

MapReader::MapReader() {}

MapReader::~MapReader() {
    this->mapfile.close();
    for(int i = rows - 1; i >= 0; i--) {
        delete map[i];
    }
    delete map;
}

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

void MapReader::generateTiles() {
    tiles.reserve(rows * cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(map[i][j] == WALL) {
                Tile tile(nullptr,
                          j * tileWidth,
                          i * tileHeight);
                tile.setHeight(tileHeight);
                tile.setWidth(tileWidth);
                tiles.push_back(tile);
            }
        }
    }
}

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

SDL_Point MapReader::getDimensions() {
    SDL_Point dimensions = {rows, cols};
    return dimensions;
}

SDL_Point MapReader::getTileDimensions() {
    SDL_Point tileDimensions = {tileWidth, tileHeight};
    return tileDimensions;
}

std::vector<Tile>* MapReader::getTiles() {
    return &tiles;
}