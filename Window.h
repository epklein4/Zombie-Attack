#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Player.h"
#include "Zombie.h"
#include "Tile.h"
#include "MapReader.h"
#include "Button.h"

class Window {
    public:
        Window(char* title, int width, int height);
        ~Window();

        void startMap();

        void clear();
        void update();
        void draw();

        void addPlayer(Player* player);
        void addZombie(Zombie* zombie);
        void addTile(Tile tile);

        SDL_Point getMapTileDimensions();
        void setTiles(std::vector<Tile>* tiles);

        bool pollEvents();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        MapReader map;

        char* title;
        int width;
        int height;
        Player* player;
        std::vector<Tile>* tiles;
        std::vector<Zombie> zombies;

        SDL_Texture* testImage;
};

#endif