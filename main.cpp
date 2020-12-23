#include "Window.h"
#include "Player.h"

int main(int argc, char* argv[]) {
    Window window((char*)"Zombie Attack", 800, 600);

    bool running = true;

    window.startMap();
    Player player(30, 30, 20, 20, window.getMapTileDimensions().x, window.getMapTileDimensions().y);
    Zombie zombie(400, 400, 30, 30);

    window.addPlayer(&player);
    window.addZombie(&zombie);

    while(running) {
        running = window.pollEvents();

        window.clear();
        window.update();
        window.draw();
    }

    return 0;
}