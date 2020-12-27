
#include "Projectile.h"

#include <cstdio>

Projectile::Projectile(int x, int y, int width, int height, double speedX, double speedY) : Entity(x, y, width, height) {
    this->xSpeed = speedX;
    this->ySpeed = speedY;
    this->color = {0, 0, 0};
}

Projectile::~Projectile() {}

void Projectile::update() {
    position.x += xSpeed;
    position.y += ySpeed;
}