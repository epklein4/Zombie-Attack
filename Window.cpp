#include "Window.h"

//window constructor
Window::Window(char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    this->width = width;
    this->height = height;
    this->paused = false;
    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetWindowMinimumSize(window, 800, 600);
    SDL_SetWindowResizable(window, SDL_FALSE);
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Window::startMap() {
    map.init("Resources/tilemap.txt", width, height);
    setTiles(map.getTiles());
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 111, 161, 161, 255);
    SDL_RenderClear(renderer);
}

void Window::update() {
    if(paused) {

    }else if(player != NULL) {
        player->updateBoundingBox();
        if(player->getShooting()) {
            Projectile* projectile = player->fire();
            if(projectile != nullptr) {
                projectiles.push_back(*projectile);
            }
        }
        for(Tile &tile : *tiles) {
            tile.updateBoundingBox();
            player->checkMovementCollision(tile.getBoundingBox());   
        }
        for(Zombie &zombie : zombies) {
            zombie.updateBoundingBox();
            if(player->getBoundingBox().checkCollision(zombie.getBoundingBox())) {
                player->kill();
            }
        }
        for(int i = 0; i < projectiles.size(); i++) {
            projectiles.at(i).update();
            projectiles.at(i).updateBoundingBox();
            for(Tile tile : *tiles) {
                if(projectiles.at(i).getBoundingBox().checkCollision(tile.getBoundingBox())) {
                    projectiles.erase(projectiles.begin() + i);
                    i--;
                    goto collided;
                }
            }
            for(int j = 0; j < zombies.size(); j++) {
                if(projectiles.at(i).getBoundingBox().checkCollision(zombies.at(j).getBoundingBox())) {
                    zombies.erase(zombies.begin() + j);
                    projectiles.erase(projectiles.begin() + i);
                    j--;
                    i--;
                    goto collided;
                }
            }
            collided: ;
        }
        player->applyMovement();
    }
}

void Window::draw() {
    if(player != NULL) { player->draw(); }
    for(Zombie zombie : zombies) {
        zombie.setRenderer(renderer);
        zombie.draw();
    }
    for(Tile tile : *tiles) { 
        tile.draw(); 
    }
    for(Button button : buttons) {
        button.setRenderer(renderer);
        button.draw();
    }
    for(Projectile projectile : projectiles) {
        projectile.setRenderer(renderer);
        projectile.draw();
    }
    SDL_RenderPresent(renderer);
}

void Window::pause() {
    paused = !paused;
    if(paused) {
        buttons.clear();
        Button pauseImage("PAUSE", -1, 50, 50, 300, 100);
        Button quitButton("BUTTON_QUIT", QUIT_BUTTON, 50, 150, 192, 64);
        buttons.push_back(pauseImage);
        buttons.push_back(quitButton);
    } else {
        buttons.clear();
    }
}

void Window::addPlayer(Player* player) {
    this->player = player;
    this->player->setRenderer(renderer);
}

void Window::addZombie(Zombie* zombie) {
    zombies.push_back(*zombie);
}

void Window::addTile(Tile tile) {
    this->tiles->push_back(tile);
    tile.setRenderer(renderer);
}

void Window::addButton(Button* button) {
    this->buttons.push_back(*button);
    button->setRenderer(renderer);
}

SDL_Point Window::getMapTileDimensions() {
    SDL_Point tileDimensions = {map.getTileDimensions().x, map.getTileDimensions().y};
    return tileDimensions;
}

void Window::setTiles(std::vector<Tile>* tiles) {
    this->tiles = tiles;
    for(Tile &tile : *tiles) {
        tile.setRenderer(renderer);
    }
}

//returns true or false for quit events
bool Window::pollEvents() {
    bool running = true;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT: running = false; break;
            case SDL_MOUSEBUTTONUP:
                for(Button &button : buttons) {
                    if(button.clicked()) {
                        switch(button.getType()) {
                            case QUIT_BUTTON: running = false; break;
                        }
                    }
                }
                player->setShooting(false);
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(Button &button : buttons) {
                    button.pressed();
                }
                player->setShooting(true);
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    int oldWindowWidth = width;
                    int oldWindowHeight = height;
                    SDL_GetWindowSize(window, &width, &height);
                    map.resize(width, height);
                    player->resize(width, height, oldWindowWidth, oldWindowHeight);
                }
                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_ESCAPE) { pause(); }
                break;
        }
        if(this->player != NULL && !paused) { this->player->readInputs(&event); }
    }
    if(this->player != NULL && !paused) { this->player->calculateMovement(); }
    return running;
}