#include "Zombie.h"
#include <time.h>

/*
 *  Creates a zombie(subclass of Entity) given position and dimensions
 */ 
Zombie::Zombie(int x, int y, int w, int h) : Entity(x, y, w, h) {
    this->color = {17, 118, 127, 255};
    this->xSpeed = 1;
    this->ySpeed = 1;
    this->spawning = true;
}

Zombie::~Zombie() {}

/*
 *  Given a direction, tells the zombie to walk in that direction
 */
void Zombie::walk(SDL_Point direction) {
    addVelocityX(xSpeed * direction.x);
    addVelocityY(ySpeed * direction.y);
}

/*
 *  Attempts to spawn the zombie in a random direction within a number of attempts
 * 
 *  If the current spawn location is not spawnable tries to find a new location
 * 
 *  If no location is found in the number of attempts, returns a nullptr
 */
Zombie* Zombie::spawn(int windowWidth, int windowHeight, std::vector<Tile>* tiles) {
    int maxSpawnAttempts = 10;
    int zombieWidth = 15;
    int zombieHeight = 15;
    int x, y;
    bool spawnable;
    BoundingBox spawnBounds;
    
    for(int attempt = 0; attempt < maxSpawnAttempts; attempt++) {
        spawnable = true;
        x = rand() * ((1 + windowWidth)) / (RAND_MAX + 1.0);
        y = rand() * ((1 + windowHeight)) / (RAND_MAX + 1.0);
        spawnBounds.updateBoundingBox(x, y, zombieWidth, zombieHeight);
        for(Tile &tile : *tiles) {
            if(spawnBounds.checkCollision(tile.getBoundingBox())) {
                spawnable = false;
            }
        }
        if(spawnable) { return new Zombie(x, y, zombieWidth, zombieHeight); }
    }
    return nullptr;
}
