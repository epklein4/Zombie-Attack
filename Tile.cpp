#include "Tile.h"

#include <SDL2/SDL_image.h>

/*
 *  Creates a tile given a renderer to draw to, positions
 * 
 *  This constructor requires the use of setter functions for dimensions
 */
Tile::Tile(SDL_Renderer* renderer, int x, int y) {
    this->position.x = x;
    this->position.y = y;
    this->renderer = renderer;
    this->texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("Resources/Tile.png"));
}

/*
 *  Creates a tile given a renderer to draw to, position, and dimensions
 */
Tile::Tile(SDL_Renderer* renderer, int x, int y, int w, int h) : Tile(renderer, x, y) {
    this->width = w;
    this->height = h;
}

Tile::~Tile() {}

/*
 *  Draws the tile to the renderer
 */
void Tile::draw() {
    SDL_Rect model{position.x, position.y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &model);
}

/*
 *  Updates the bounding box of the tile, given its current position and dimensions
 */
void Tile::updateBoundingBox() {
    this->boundingBox.updateBoundingBox(position.x, position.y, width, height);
}

/*
 *  Gets the position of the tile
 */
SDL_Point Tile::getPosition() {
    return this->position;
}

/*
 *  Sets the position of the tile
 */
void Tile::setPosition(int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

/*
 *  Sets the width of the tile
 */
void Tile::setWidth(int width) { this->width = width; }

/*
 *  Sets the height of the tile
 */
void Tile::setHeight(int height) { this->height = height; }

/*
 *  Sets the renderer for the tile to draw to and loads the tile image
 */
void Tile::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("Resources/Tile.png"));
}

/*
 *  Gets the tile's width and height
 */
SDL_Point Tile::getDimensions() {
    return {width, height};
}

/*
 *  Gets the tile's Bounding Box
 */
BoundingBox Tile::getBoundingBox() {
    return this->boundingBox;
}