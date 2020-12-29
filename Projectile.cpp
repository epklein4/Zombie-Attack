
#include "Projectile.h"

#include <cstdio>

Projectile::Projectile(int x, int y, int width, int height, double xSpeed, double ySpeed)
: Entity(x, y, width, height) {
    this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;
    this->x = x;
    this->y = y;
    this->color = {0, 0, 0};
}

Projectile::~Projectile() {}

void Projectile::update() {
    this->x += xSpeed;
    this->y += ySpeed;
    position.x = x;
    position.y = y;
}