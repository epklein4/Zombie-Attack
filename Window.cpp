#include "Window.h"

//window constructor
Window::Window(char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    this->width = width;
    this->height = height;
    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetWindowMinimumSize(window, 800, 600);
    SDL_SetWindowResizable(window, SDL_FALSE);

    testImage = SDL_CreateTextureFromSurface(renderer, IMG_Load("Resources/BUTTON_TEMPLATE.png"));
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
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);
}

void Window::update() {
    if(player != NULL) {
        player->updateBoundingBox();
        for(Tile &tile : *tiles) {
            tile.updateBoundingBox();
            player->checkMovementCollision(tile.getBoundingBox());   
        }
        for(Zombie zombie : zombies) {
            zombie.updateBoundingBox();
            if(player->getBoundingBox().checkCollision(zombie.getBoundingBox())) {
                player->kill();
            }
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
        tile.setRenderer(renderer);
        tile.draw(); 
    }
    SDL_Rect testImageRect{400, 400, 96*2, 32*2};
    SDL_RenderCopyEx(renderer, testImage, NULL, &testImageRect, 15, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
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

SDL_Point Window::getMapTileDimensions() {
    SDL_Point tileDimensions = {map.getTileDimensions().x, map.getTileDimensions().y};
    return tileDimensions;
}

void Window::setTiles(std::vector<Tile>* tiles) {
    this->tiles = tiles;
}

//returns true or false for quit events
bool Window::pollEvents() {
    bool running = true;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT: running = false; break;
            case SDL_MOUSEBUTTONUP:
                break;
            case SDL_MOUSEBUTTONDOWN:
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
                if(event.key.keysym.sym == SDLK_ESCAPE) { running = false; }
                break;
        }
        if(this->player != NULL) { this->player->readInputs(&event); }
    }
    if(this->player != NULL) { this->player->calculateMovement(); }
    return running;
}