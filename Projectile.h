#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include "Entity.h"

class Projectile : public Entity{
    public:
        Projectile(int x, int y, int width, int height , SDL_Point velocities);
        ~Projectile();

        void update();

    private:
        SDL_Renderer* renderer;
        BoundingBox boundingBox;

};

#endif