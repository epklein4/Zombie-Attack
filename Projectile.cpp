
#include "Projectile.h"

#include <cstdio>

Projectile::Projectile(int x, int y, int width, int height, SDL_Point velocities) : Entity(x, y, width, height) {
    this->xSpeed = velocities.x;
    this->ySpeed = velocities.y;
    this->color = {0, 0, 0};
}

Projectile::~Projectile() {}

void Projectile::update() {
    position.x += xSpeed;
    position.y += ySpeed;
}