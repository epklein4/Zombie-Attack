#include "Entity.h"

#include <cstdio>

Entity::Entity(int x, int y, int width, int height) {
    this->width = width;
    this->height = height;
    this->position.x = x;
    this->position.y = y;
    this->velocity = new SDL_Point({0, 0});
}

Entity::~Entity() {}

void Entity::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Entity::setVelocityX(int x) { velocity->x = x; }
void Entity::setVelocityY(int y) { velocity->y = y; }

int Entity::getVelocityX() { return velocity->x; }
int Entity::getVelocityY() { return velocity->y; }

void Entity::checkMovementCollision(BoundingBox other) {
    BoundingBox movementBoxX;
    BoundingBox movementBoxY;

    movementBoxX.updateBoundingBox(position.x + velocity->x, position.y, width, height);
    movementBoxY.updateBoundingBox(position.x, position.y + velocity->y, width, height);

    if(other.checkCollision(movementBoxX)) {
        if(velocity->x > 0) {
            position.x += other.getBounds().x - (position.x + width) - 1;
        } else if(velocity->x < 0) {
            position.x -= position.x - (other.getBounds().x + other.getBounds().w) - 1;
        }
         velocity->x = 0; 
    }
    if(other.checkCollision(movementBoxY)) {
        if(velocity->y > 0) {
            position.y += other.getBounds().y - (position.y + height) - 1;
        } else if(velocity->y < 0) {
            position.y -= position.y - (other.getBounds().y + other.getBounds().h) - 1;
        }
         velocity->y = 0; 
    }
}

void Entity::applyMovement() {
    position.x += velocity->x;
    position.y += velocity->y;
    velocity->x = 0;
    velocity->y = 0;
}

SDL_Point Entity::getPostition() {
    return position;
}

SDL_Point Entity::getDimensions() {
    return {width, height};
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