#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include "BoundingBox.h"

class Entity{
    public:
        Entity(int x, int y, int w, int h);
        ~Entity();

        void draw();

        void resize(int windowWidth, int windowHeight, int oldWindowWidth, int oldWindowHeight);

        void setRenderer(SDL_Renderer* renderer);

        void setVelocityX(int x);
        void setVelocityY(int y);
        void addVelocityX(int x);
        void addVelocityY(int y);

        int getVelocityX();
        int getVelocityY();

        void checkMovementCollision(BoundingBox other);
        void applyMovement();

        SDL_Point getPostition();
        SDL_Point getDimensions();
        BoundingBox getBoundingBox();

        void updateBoundingBox();

    private:
        SDL_Renderer* renderer;

        BoundingBox boundingBox;

    protected:
        SDL_Point position;
        SDL_Point* velocity;
        SDL_Color color;
        int xSpeed;
        int ySpeed;

        int width;
        int height;

};

#endif