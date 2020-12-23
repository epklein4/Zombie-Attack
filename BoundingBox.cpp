#include "BoundingBox.h"

BoundingBox::BoundingBox() {}
BoundingBox::~BoundingBox() {}

void BoundingBox::updateBoundingBox(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

//returns true if bounding boxes collide
bool BoundingBox::checkCollision(BoundingBox other) {
    return !((this->x + this->width < other.x || this->x > other.x + other.width) ||
             (this->y + this->height < other.y || this->y > other.y + other.height)); 
}

SDL_Rect BoundingBox::getBounds() {
    return {x, y, width, height};
}