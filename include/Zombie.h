#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"
#include "Tile.h"
#include <vector>

class Zombie : public Entity {
    public:
        Zombie(int x, int y, int w, int h);
        ~Zombie();

        void walk(SDL_Point direction);
        static Zombie* spawn(int windowWidth, int windowHeight, std::vector<Tile>* tiles);
    private:
        bool spawning;
};

#endif