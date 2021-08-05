#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"
#include "Tile.h"
#include <vector>
#include <chrono>

#define SPAWN_TIME 1500

class Zombie : public Entity {
    public:
        Zombie(int x, int y, int w, int h);
        ~Zombie();

        void walk(SDL_Point direction);
        static Zombie* spawn(int windowWidth, int windowHeight, std::vector<Tile>* tiles);

        void checkDoneSpawning();
        void spawningGrow();

        bool getSpawning();
    private:
        bool spawning;
        std::chrono::system_clock::time_point spawnTime;
        SDL_Rect* fullDimensions;
        SDL_Rect* startDimensions;
};

#endif