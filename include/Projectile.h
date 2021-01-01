#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include "Entity.h"

class Projectile : public Entity{
    public:
        Projectile(int x, int y, int width, int height , double xSpeed, double ySpeed);
        ~Projectile();

        void update();

    private:
        SDL_Renderer* renderer;
        BoundingBox boundingBox;
        double x;
        double y;
        double xSpeed;
        double ySpeed;

};

#endif