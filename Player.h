#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include "Entity.h"

class Player : public Entity {
    public:
        Player(int x, int y, int w, int h, int tileWidth, int tileHeight);

        void readInputs(SDL_Event* event);

        void calculateMovement();
        void checkMovementCollision(BoundingBox other);
        void applyMovement();

        void kill();

        std::unordered_map<std::string, bool> getInputs();

    private:
        std::unordered_map<std::string, bool> inputs;
        
        bool living;

};

#endif