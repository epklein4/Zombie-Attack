#include "Window.h"
#include "Entity.h"
#include "Button.h"

#include <chrono>
#include <thread>
#include <iostream>

auto timeA = std::chrono::system_clock::now();
auto timeB = std::chrono::system_clock::now();

/*
 *  Entry point for the program
 */
int main(int argc, char* argv[]) {

    Window window((char*)"Zombie Attack", 800, 600);

    bool running = true;

    window.startMap();
    
    while(running) {
        timeA = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli>  delta = timeA - timeB;

        if(delta.count() < 16.667) {
            std::chrono::duration<double, std::milli> delta_ms(16.667 - delta.count());
            auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
            std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
        }

        timeB = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> sleepTime = timeB - timeA;

        // std::cout << (delta + sleepTime).count() << std::endl;

        running = window.pollEvents();

        window.clear();
        window.update();
        window.draw();

    }

    return 0;
}