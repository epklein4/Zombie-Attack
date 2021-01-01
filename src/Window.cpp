#include "Window.h"
#include <time.h>

/*
 *  Creates the window for displaying to the user
 *  Also initizializes music and SFX
 */
Window::Window(char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    this->width = width;
    this->height = height;
    this->paused = false;
    this->lastSpawned = std::chrono::system_clock::now();
    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetWindowMinimumSize(window, 800, 600);
    SDL_SetWindowResizable(window, SDL_FALSE);

    SDL_ShowCursor(0);
    cursor = SDL_CreateTextureFromSurface(renderer, IMG_Load("Resources/CROSSHAIR.png"));
    
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,
                  MIX_DEFAULT_FORMAT,
                  1, 2048);

    bgMusic = Mix_LoadMUS("Resources/BG_Music.wav");
    bulletSFX = Mix_LoadWAV("Resources/BulletSFX.wav");
    Mix_PlayMusic(bgMusic, -1);
}

/*
 *  Destroys SDL resources
 */
Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}

/*
 *  Starts the map for a level
 *  Initializes the maps pathfinder
 */
void Window::startMap() {
    srand(time(NULL));
    map.init("Resources/tilemap.txt", width, height);
    setTiles(map.getTiles());
    pathfinder = new Pathfinder(map.getDimensions().x, map.getDimensions().y, tiles);
}

/*
 *  Clears the window
 */
void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 240, 235, 192, 255);
    SDL_RenderClear(renderer);
}

/*
 *  Logic for interaction between different world objects
 * 
 *  If the game is paused no updates to logic will occur
 */
void Window::update() {
    if(paused) {
    }else if(player != NULL) {
        if(zombies.size() < ZOMBIE_LIMIT) {
            spawnTimer();
        }
        pathfinder->setGoal(player->getPostition().x + (player->getDimensions().x / 2),
                            player->getPostition().y + (player->getDimensions().x / 2));
        player->updateBoundingBox();
        if(player->getShooting()) {
            Projectile* projectile = player->fire();
            if(projectile != nullptr) {
                Mix_PlayChannel(-1, bulletSFX, 0);
                projectiles.push_back(*projectile);
            }
        }
        for(Tile &tile : *tiles) {
            tile.updateBoundingBox();
            player->checkMovementCollision(tile.getBoundingBox());   
        }
        for(Zombie &zombie : zombies) {
            zombie.updateBoundingBox();
            SDL_Point direction = pathfinder->getPath(zombie.getPostition().x + (zombie.getDimensions().x / 2),
                                                      zombie.getPostition().y + (zombie.getDimensions().y / 2));
            zombie.walk(direction);
            for(Zombie &otherZ : zombies) {
                if(&otherZ == &zombie) { continue; }
                zombie.checkMovementCollision(otherZ.getBoundingBox());
                zombie.updateBoundingBox();
            }
            for(Tile &tile : *tiles) {
                zombie.checkMovementCollision(tile.getBoundingBox());   
                zombie.updateBoundingBox();
            }
            if(player->getBoundingBox().checkCollision(zombie.getBoundingBox())) {
                player->kill();
                pause();
            }
            zombie.applyMovement();
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

/*
 *  Draws everything in the window
 */
void Window::draw() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect cursorRect{mouseX-8, mouseY-8, 16, 16};
    if(player != NULL) { player->draw(); }
    for(Zombie zombie : zombies) {
        zombie.setRenderer(renderer);
        zombie.draw();
    }
    for(Tile tile : *tiles) { 
        tile.draw(); 
    }
    for(Projectile projectile : projectiles) {
        projectile.setRenderer(renderer);
        projectile.draw();
    }
    for(Button button : buttons) {
        button.setRenderer(renderer);
        button.draw();
    }
    SDL_RenderCopy(renderer, cursor, NULL, &cursorRect);
    SDL_RenderPresent(renderer);
}

/*
 *  Pauses and unpauses the game
 * 
 *  During pauses creates ui elements for navigation
 */
void Window::pause() {
    paused = !paused;
    if(paused) {
        buttons.clear();
        Button pauseImage("PAUSE", -100, 50, 50, 300, 100);
        Button restartButton("BUTTON_RESTART", RESTART_BUTTON, 50, 150, 192, 64);
        Button quitButton("BUTTON_QUIT", QUIT_BUTTON, 50, 230, 192, 64);
        buttons.push_back(pauseImage);
        buttons.push_back(restartButton);
        buttons.push_back(quitButton);
        Mix_PauseMusic();
    } else {
        Mix_ResumeMusic();
        buttons.clear();
    }
}

/*  ////UNIMPLEMENTED////
 *  Restarts the level
 */
void Window::restart() {
    tiles->clear();
    buttons.clear();
    zombies.clear();
    projectiles.clear();
}

/*
 *  Polls for user input and begins interpretting
 */
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
                            case RESTART_BUTTON: restarted = true; break;
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

/*
 *  Spawns a zombie if a interval has passed
 */
void Window::spawnTimer() {
    auto now = std::chrono::system_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSpawned);
    if(elapsedTime > std::chrono::milliseconds(1000)) {
        lastSpawned = std::chrono::system_clock::now();
        addZombie(Zombie::spawn(width, height, tiles));
    }
}

/*
 *  Adds the player to the world
 */
void Window::addPlayer(Player* player) {
    this->player = player;
    this->player->setRenderer(renderer);
}

/*
 *  Adds a zombie to the world
 */
void Window::addZombie(Zombie* zombie) {
    if(zombie == nullptr) { return; }
    zombies.push_back(*zombie);
}

/*
 *  Adds a tile to the world
 */
void Window::addTile(Tile tile) {
    this->tiles->push_back(tile);
    tile.setRenderer(renderer);
}

/*
 *  Adds a button to the world
 */
void Window::addButton(Button* button) {
    this->buttons.push_back(*button);
    button->setRenderer(renderer);
}

/*
 *  Gets the maps dimensions
 */
SDL_Point Window::getMapTileDimensions() {
    SDL_Point tileDimensions = {map.getTileDimensions().x, map.getTileDimensions().y};
    return tileDimensions;
}

/*
 *  Sets the worlds tiles to a given list of tiles
 */
void Window::setTiles(std::vector<Tile>* tiles) {
    this->tiles = tiles;
    for(Tile &tile : *tiles) {
        tile.setRenderer(renderer);
    }
}

