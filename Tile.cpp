#include "Tile.h"

#include <SDL2/SDL_image.h>

#include <cstdio>

void Tile::printDimensions() {
    printf("Dimensions:\nx: %d  y: %d\nw: %d  h: %d\n", position.x, position.y, width, height);
}

Tile::Tile(SDL_Renderer* renderer, int x, int y) {
    this->position.x = x;
    this->position.y = y;
    this->renderer = renderer;
    this->texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("Resources/Tile.png"));
}

Tile::Tile(SDL_Renderer* renderer, int x, int y, int w, int h) : Tile(renderer, x, y) {
    this->width = w;
    this->height = h;
}

Tile::~Tile() {}

void Tile::draw() {
    SDL_Rect model{position.x, position.y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &model);
}

void Tile::updateBoundingBox() {
    this->boundingBox.updateBoundingBox(position.x, position.y, width, height);
}

SDL_Point Tile::getPosition() {
    return this->position;
}

void Tile::setPosition(int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

void Tile::setWidth(int width) { this->width = width; }

void Tile::setHeight(int height) { this->height = height; }

void Tile::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("Resources/Tile.png"));
}

SDL_Point Tile::getDimensions() {
    return {width, height};
}

BoundingBox Tile::getBoundingBox() {
    return this->boundingBox;
}