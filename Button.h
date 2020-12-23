#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

class Button {
    public:
        Button(int x, int y, int width, int height);
        ~Button();

        bool clicked();
        bool pressed();

        void setRenderer(SDL_Renderer* renderer);

        void draw();

    private:
        SDL_Renderer* renderer;
        SDL_Rect surface;
        
        bool isPressed;
};

#endif