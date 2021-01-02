#include "Window.h"
#include "Entity.h"
#include "Button.h"

/*
 *  Entry point for the program
 */
int main(int argc, char* argv[]) {

    Window window((char*)"Zombie Attack", 800, 600);

    bool running = true;

    window.startMap();
    
    while(running) {
        running = window.pollEvents();

        window.clear();
        window.update();
        window.draw();
    }

    return 0;
}