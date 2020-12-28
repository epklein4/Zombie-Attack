#include "Window.h"
#include "Entity.h"
#include "Button.h"

int main(int argc, char* argv[]) {

    Window window((char*)"Zombie Attack", 800, 600);

    bool running = true;

    window.startMap();
    Player player(400, 300, 20, 20, window.getMapTileDimensions().x, window.getMapTileDimensions().y);

    window.addPlayer(&player);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 2; j++) {
            Zombie* zombie = new Zombie(400 + j*20, 100 + i*20, 15, 15);
            window.addZombie(zombie);
        }
    }

    while(running) {
        running = window.pollEvents();

        window.clear();
        window.update();
        window.draw();
    }

    return 0;
}