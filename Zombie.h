#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"

class Zombie : public Entity {
    public:
        Zombie(int x, int y, int w, int h);
        ~Zombie();

        void walk(SDL_Point direction);
    private:
};

#endif