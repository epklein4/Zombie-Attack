#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <string>

#define QUIT_BUTTON 0

class Button {
    public:
        Button(std::string textureName, int buttonType, int x, int y, int width, int height);
        Button();
        ~Button();

        bool clicked();
        bool pressed();

        int getType();
        void setRenderer(SDL_Renderer* renderer);

        void draw();

    private:
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Texture* downTexture;
        SDL_Rect surface;
        char* textureName;
        char* downTextureName;

        int buttonType;
        
        bool isPressed;
};

#endif