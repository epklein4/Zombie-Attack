#include "Tile.h"

#include <cstdio>

void Tile::printDimensions() {
    printf("Dimensions:\nx: %d  y: %d\nw: %d  h: %d\n", position.x, position.y, width, height);
}

Tile::Tile(int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

Tile::~Tile() {}

void Tile::draw() {
    SDL_Rect model{position.x, position.y, width, height};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &model);
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

void Tile::setWidth(int width) {
    this->width = width;
}

void Tile::setHeight(int height) {
    this->height = height;
}

void Tile::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

BoundingBox Tile::getBoundingBox() {
    return this->boundingBox;
}