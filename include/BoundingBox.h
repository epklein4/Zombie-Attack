#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <SDL2/SDL.h>

class BoundingBox {
    public:
        BoundingBox();
        ~BoundingBox();

        void updateBoundingBox(int x, int y, int width, int height);

        bool checkCollision(BoundingBox other);

        SDL_Rect getBounds();

    private:
        int x;
        int y;
        int width;
        int height;
};

#endif