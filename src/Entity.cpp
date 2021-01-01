#include "Entity.h"

#include <cstdio>

/*
 *  Constructor for a basic Entity
 *  Requires the Entity's position and dimensions
 * 
 *  Entity should be considered abstract, though it is implemented such that it
 *  can be used for test entities
 */
Entity::Entity(int x, int y, int width, int height) {
    this->width = width;
    this->height = height;
    this->position.x = x;
    this->position.y = y;
    this->velocity = new SDL_Point({0, 0});
}

Entity::~Entity() {}

/*
 *  Sets the renderer for an Entity or Entity child to draw to
 */
void Entity::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

/*
 *  Functions for setting the entity's x or y velocity
 */
void Entity::setVelocityX(int x) { velocity->x = x; }
void Entity::setVelocityY(int y) { velocity->y = y; }

/*
 *  Functions for adding to the entity's x or y velocity 
 */
void Entity::addVelocityX(int x) { velocity->x += x; }
void Entity::addVelocityY(int y) { velocity->y += y; }

/*
 *  Functions to get the entity's current x or y velocity
 */
int Entity::getVelocityX() { return velocity->x; }
int Entity::getVelocityY() { return velocity->y; }

/*
 *  Creates two Bounding Boxes that would be where the entity would move in the next
 *  frame given its current velocity
 * 
 *  If the entity would collide with the given Bounding Box, other, the entity's
 *  velocity is reduced to zero in that direction and the entity is placed touching the 
 *  Bounding Box
 */
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

/*
 *  Limits the velocity to a max speed and then adds the velocity to the current position
 */
void Entity::applyMovement() {
    if(velocity->x > xSpeed) { velocity->x = xSpeed; }
    if(velocity->y > ySpeed) { velocity->y = ySpeed; }
    if(velocity->x < -xSpeed) { velocity->x = -xSpeed; }
    if(velocity->y < -ySpeed) { velocity->y = -ySpeed; }
    position.x += velocity->x;
    position.y += velocity->y;
}

/*
 *  Returns the position of the entity
 */
SDL_Point Entity::getPostition() {
    return position;
}

/*
 *  Returns the dimensions of the entity
 */
SDL_Point Entity::getDimensions() {
    return {width, height};
}

/*
 *  Returns the Bounding Box of the entity
 */
BoundingBox Entity::getBoundingBox() {
    return this->boundingBox;
}

/*
 *  Updates the Bounding Box of the entity with the current position and dimensions of
 *  the entity
 */
void Entity::updateBoundingBox() {
    this->boundingBox.updateBoundingBox(position.x, position.y, width, height);
}

/*
 *  Draws the entity to the currents SDL Renderer
 */
void Entity::draw() {
    SDL_Rect model{position.x, position.y, width, height};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &model);
}

/*
 *  Updates the dimensions of the of the entity based on the change of the display
 *  windows dimensions
 */
void Entity::resize(int windowWidth, int windowHeight, int oldWindowWidth, int oldWindowHeight) {
    this->width = ((double)width / oldWindowWidth) * windowWidth;
    this->height = ((double)height / oldWindowHeight) * windowHeight;
    this->position.x = ((double)position.x / oldWindowWidth) * windowWidth;
    this->position.y = ((double)position.y / oldWindowHeight) * windowHeight;
}