
#include "Zombie.h"
#include <time.h>

Zombie::Zombie(int x, int y, int w, int h) : Entity(x, y, w, h) {
    this->color = {17, 118, 127, 255};
    this->xSpeed = 2;
    this->ySpeed = 2;
    srand(time(NULL));
}

Zombie::~Zombie() {}

void Zombie::walk(SDL_Point direction) {
    addVelocityX(xSpeed * direction.x);
    addVelocityY(ySpeed * direction.y);
}
