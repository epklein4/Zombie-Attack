#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include "BoundingBox.h"

class Tile {
    public:
        Tile(SDL_Renderer* renderer, int x, int y);
        Tile(SDL_Renderer* renderer, int x, int y, int w, int h);
        ~Tile();

        void draw();
        
        void updateBoundingBox();

        SDL_Point getPosition();

        void setPosition(int x, int y);
        void setWidth(int width);
        void setHeight(int height);
        void setRenderer(SDL_Renderer* renderer);

        void printDimensions();

        SDL_Point getDimensions();
        BoundingBox getBoundingBox();

    private:
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Point position;

        BoundingBox boundingBox;

        int width;
        int height;
    
};

#endif