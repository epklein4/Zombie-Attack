
#include "Button.h"
#include <SDL2/SDL_image.h>

/*
 *  Constructor for a new button object
 *  Requires the button's name, type, position, and dimensions
 * 
 *  Loads the image for the down and up positions of the button
 */
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

/*
 *  Sets the SDL Renderer of for drawing 
 *  Loads the down and up images to an SDL surface
 *  
 *  If there is no down image, uses the up image instead
 */
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

/*
 *  Returns the type of button for interpreting what to do on a click event
 */
int Button::getType() {
    return this->buttonType;
}

/* 
 *  Returns true if the button is was pressed and is then released while the mouse
 *  is still over the button
 */
bool Button::clicked() {
    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if((mouseX > surface.x && mouseX < surface.x + surface.w) &&
       (mouseY > surface.y && mouseY < surface.y + surface.h) && isPressed) {
        isPressed = false;
        return true;
    }
    isPressed = false;
    return false;
}

/*
 *  Returns true if the button is pressed(The left mouse button is down while the
 *  cursor is over the button)
 */
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

/*
 *  Draws the button to its given renderer based on its current pressed state
 */
void Button::draw() {
    if(isPressed) {
        SDL_RenderCopy(renderer, downTexture, NULL, &surface);
    } else {
        SDL_RenderCopy(renderer, texture, NULL, &surface);
    }
}