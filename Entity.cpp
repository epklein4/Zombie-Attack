#include "Entity.h"

#include <cstdio>

Entity::Entity(int x, int y, int width, int height) {
    this->width = width;
    this->height = height;
    this->position.x = x;
    this->position.y = y;
    this->velocity.x = 0;
    this->velocity.y = 0;
}

Entity::~Entity() {}

void Entity::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Entity::setVelocityX(int x) { velocity.x = x; }
void Entity::setVelocityY(int y) { velocity.y = y; }

SDL_Point Entity::getPostition() {
    return position;
}

BoundingBox Entity::getBoundingBox() {
    return this->boundingBox;
}

void Entity::updateBoundingBox() {
    this->boundingBox.updateBoundingBox(position.x, position.y, width, height);
}

void Entity::draw() {
    SDL_Rect model{position.x, position.y, width, height};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &model);
}

void Entity::resize(int windowWidth, int windowHeight, int oldWindowWidth, int oldWindowHeight) {
    this->width = ((double)width / oldWindowWidth) * windowWidth;
    this->height = ((double)height / oldWindowHeight) * windowHeight;
    this->position.x = ((double)position.x / oldWindowWidth) * windowWidth;
    this->position.y = ((double)position.y / oldWindowHeight) * windowHeight;
}