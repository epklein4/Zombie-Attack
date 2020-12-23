
#include "Zombie.h"

Zombie::Zombie(int x, int y, int w, int h) : Entity(x, y, w, h) {
    this->color = {0, 80, 0, 255};
}

Zombie::~Zombie() {}

