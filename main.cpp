#include "Window.h"
#include "Entity.h"
#include "Button.h"

int main(int argc, char* argv[]) {

    Window window((char*)"Zombie Attack", 800, 600);

    bool running = true;

    window.startMap();
    Player player(200, 300, 20, 20, window.getMapTileDimensions().x, window.getMapTileDimensions().y);

    window.addPlayer(&player);
    
    while(running) {
        running = window.pollEvents();

        window.clear();
        window.update();
        window.draw();
    }

    return 0;
}