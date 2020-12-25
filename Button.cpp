
#include "Button.h"
#include <SDL2/SDL_image.h>

Button::Button(std::string textureName, int buttonType, int x, int y, int width, int height) {
    std::string fullTexture = "Resources/" + textureName + ".png";
    std::string fullDownTexture = "Resources/" + textureName + "_DOWN.png";
    this->textureName = new char[fullTexture.length()+1];
    this->downTextureName = new char[fullDownTexture.length()+1];
    strcpy(this->textureName, fullTexture.c_str());
    strcpy(this->downTextureName, fullDownTexture.c_str());
    this->buttonType = buttonType;

    surface = {x, y, width, height};
    isPressed = false;
}

Button::Button() {}
Button::~Button() {}


void Button::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->texture = SDL_CreateTextureFromSurface(renderer, IMG_Load(textureName));
    SDL_Surface* downImage = IMG_Load(downTextureName);
    if(downImage) {
        this->downTexture = SDL_CreateTextureFromSurface(renderer, downImage);
    }else{
        this->downTexture = this->texture;
    }
}

int Button::getType() {
    return this->buttonType;
}

bool Button::clicked() {
    int mouseX;
    int mouseY;
    isPressed = false;
    SDL_GetMouseState(&mouseX, &mouseY);
    if((mouseX > surface.x && mouseX < surface.x + surface.w) &&
       (mouseY > surface.y && mouseY < surface.y + surface.h)) {
        return true;
    }
    return false;
}

bool Button::pressed() {
    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if((mouseX > surface.x && mouseX < surface.x + surface.w) &&
       (mouseY > surface.y && mouseY < surface.y + surface.h)) {
        isPressed = true;
        return true;
    }
    return false;
}

void Button::draw() {
    if(isPressed) {
        SDL_RenderCopy(renderer, downTexture, NULL, &surface);
    } else {
        SDL_RenderCopy(renderer, texture, NULL, &surface);
    }
}