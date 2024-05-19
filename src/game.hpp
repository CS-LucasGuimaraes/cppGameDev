#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <bits/stdc++.h>

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int widht, int height, bool fullscreen); 
    bool handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }

private:
    bool isRunning;
    int screen_size[2];
    SDL_Window *screen;
    SDL_Renderer *display;

}; 

#endif