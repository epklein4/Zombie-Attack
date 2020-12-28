#include "Player.h"

Player::Player(int x, int y, int w, int h, int tileWidth, int tileHeight) : Entity(x, y, w, h) {
    this->xSpeed = tileWidth / 4;
    this->ySpeed = tileHeight / 4;
    this->color = {0, 0, 0, 255};
    this->lastShotTime = std::chrono::system_clock::now();
    living = true;
    shooting = false;
}

void Player::readInputs(SDL_Event* event) {
    if(event->type == SDL_KEYDOWN) {
        switch(event->key.keysym.sym) {
            case SDLK_w: inputs["w"] = true; break;
            case SDLK_a: inputs["a"] = true; break;
            case SDLK_s: inputs["s"] = true; break;
            case SDLK_d: inputs["d"] = true; break;
        }
    }
    if(event->type == SDL_KEYUP) {
        switch(event->key.keysym.sym) {
            case SDLK_w: inputs["w"] = false; break;
            case SDLK_a: inputs["a"] = false; break;
            case SDLK_s: inputs["s"] = false; break;
            case SDLK_d: inputs["d"] = false; break;
        }
    }
}

void Player::calculateMovement() {
    if(inputs["w"] == true) { this->velocity->y -= ySpeed; }
    if(inputs["a"] == true) { this->velocity->x -= xSpeed; }
    if(inputs["s"] == true) { this->velocity->y += ySpeed; }
    if(inputs["d"] == true) { this->velocity->x += xSpeed; }
}

void Player::applyMovement() {
    if(living) {
        position.x += velocity->x;
        position.y += velocity->y;
    }
    velocity->x = 0;
    velocity->y = 0;
}

Projectile* Player::fire() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastShotTime);
    if(elapsedTime > std::chrono::milliseconds(250)) {
        int mouseX, mouseY;
        double length;
        SDL_GetMouseState(&mouseX, &mouseY);
        double velocityX = mouseX - (position.x + ((double)width / 2));
        double velocityY = mouseY - (position.y + ((double)height / 2));
        length = SDL_sqrt(SDL_pow(velocityX, 2) + SDL_pow(velocityY, 2));
        velocityX = (velocityX / length) * 10;
        velocityY = (velocityY / length) * 10;

        Projectile* projectile = new Projectile((int)(position.x + ((double)width / 2)),
                                                (int)(position.y + ((double)height / 2)),
                                                 5, 5, velocityX, velocityY);
        lastShotTime = std::chrono::system_clock::now();
        return projectile;
    }
    return nullptr;
}

void Player::kill() {
    living = false;
    color = {80, 0, 0, 255};
}

void Player::setShooting(bool shooting) {
    this->shooting = shooting;
}

bool Player::getShooting() {
    if(!living) { return false; }
    return shooting;
}

std::unordered_map<std::string, bool> Player::getInputs() {
    return this->inputs;
}