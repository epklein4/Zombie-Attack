#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <chrono>
#include "Player.h"
#include "Zombie.h"
#include "Tile.h"
#include "MapReader.h"
#include "Button.h"
#include "Projectile.h"
#include "Pathfinder.h"

#define ZOMBIE_LIMIT 200

class Window {
    public:
        Window(char* title, int width, int height);
        ~Window();

        void startMap();

        void clear();
        void update();
        void draw();

        void pause();
        void restart();

        void addPlayer(Player* player);
        void addZombie(Zombie* zombie);
        void addButton(Button* button);
        void addTile(Tile tile);

        SDL_Point getMapTileDimensions();
        void setTiles(std::vector<Tile>* tiles);

        void drawScore();

        bool pollEvents();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        Mix_Music* bgMusic;
        Mix_Chunk* bulletSFX;
        TTF_Font* scoreFont;
        SDL_Texture* cursor;
        Pathfinder* pathfinder;
        MapReader map;

        char* title;
        int width;
        int height;

        Player* player;
        std::vector<Tile>* tiles;
        std::vector<Zombie> zombies;
        std::vector<Button> buttons;
        std::vector<Projectile> projectiles;

        int score;

        std::chrono::system_clock::time_point lastSpawned;

        bool paused;
        bool restarted;

        void spawnTimer();
};

#endif