#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include <chrono>
#include "Entity.h"
#include "Projectile.h"

class Player : public Entity {
    public:
        Player(int x, int y, int w, int h, int tileWidth, int tileHeight);

        void readInputs(SDL_Event* event);

        void calculateMovement();
        void checkMovementCollision(BoundingBox other);
        void applyMovement();

        Projectile* fire();

        void kill();

        void setShooting(bool shooting);

        bool getShooting();

        std::unordered_map<std::string, bool> getInputs();

    private:
        std::unordered_map<std::string, bool> inputs;
        
        std::chrono::system_clock::time_point lastShotTime;
        bool living;
        bool shooting;

};

#endif