
#include "Button.h"

Button::Button(int x, int y, int width, int height) {
    surface = {x, y, width, height};
    isPressed = false;
}

Button::~Button() {}

void Button::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
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
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &surface);
}