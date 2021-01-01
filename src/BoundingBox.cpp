#include "BoundingBox.h"

BoundingBox::BoundingBox() {}
BoundingBox::~BoundingBox() {}

/*
 *  Sets the members of the Bounding Box to their associated parameter
 */
void BoundingBox::updateBoundingBox(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

/* 
 *  Checks whether the current Bounding Box is currently overlapping with
 *  the Bounding Box other
 */
bool BoundingBox::checkCollision(BoundingBox other) {
    return !((this->x + this->width < other.x || this->x > other.x + other.width) ||
             (this->y + this->height < other.y || this->y > other.y + other.height)); 
}

/* 
 *  Returns the dimensions of the current Bounding Box
 */
SDL_Rect BoundingBox::getBounds() {
    return {x, y, width, height};
}