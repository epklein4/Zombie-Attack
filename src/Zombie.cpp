#include "Zombie.h"
#include <time.h>

// #include <cstdio>

/*
 *  Creates a zombie(subclass of Entity) given position and dimensions
 * 
 *  Zombie starts small and grows to full size
 */ 
Zombie::Zombie(int x, int y, int w, int h) : Entity(x + (w/2), y + (h/w), 0, 0) {
    this->color = {17, 118, 127, 255};
    this->xSpeed = 1;
    this->ySpeed = 1;
    this->fullDimensions = new SDL_Rect{x, y, w, h};
    this->startDimensions = new SDL_Rect{position.x, position.y, width, height};
    this->spawning = true;
    this->spawnTime = std::chrono::system_clock::now();
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
        x = rand() % windowWidth;
        y = rand() % windowHeight;
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

/*
 *  Checks to see if the zombie should be done spawning and sets spawning to false if so
 */
void Zombie::checkDoneSpawning() {
    auto now = std::chrono::system_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - spawnTime);
    if(elapsedTime > std::chrono::milliseconds(SPAWN_TIME)) {
        spawning = false;
    }
}

/*
 *  While the zombie is still spawning, grows the zombie to full size over time;
 */
void Zombie::spawningGrow() {
    auto now = std::chrono::system_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - spawnTime);
    int time = elapsedTime.count();
    position.x = startDimensions->x - (time * ((fullDimensions->w / 2.0) / SPAWN_TIME));
    position.y = startDimensions->y - (time * ((fullDimensions->h / 2.0) / SPAWN_TIME));;
    width = startDimensions->w + (time * ((double)fullDimensions->w / SPAWN_TIME));
    height = startDimensions->h + (time * ((double)fullDimensions->h / SPAWN_TIME));

    if(position.x > fullDimensions->x) { position.x = fullDimensions->x; }
    if(position.y > fullDimensions->y) { position.y = fullDimensions->y; }
    if(width > fullDimensions->w) { width = fullDimensions->w; }
    if(height > fullDimensions->h) { height = fullDimensions->h; }
}

/*
 *  Returns true if the zombie is still spawning
 */
bool Zombie::getSpawning() { return spawning; }