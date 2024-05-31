#include "game.hpp"
int pos[2] = {21,21};


void Game::init(const char* title, int xpos, int ypos, int widht, int height, bool fullscreen) {

    int flags = 0;

    if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }

    if(SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0) {
        std::clog << "SDL2 initialized!...\n";

        this->screen_size[0] = widht; this->screen_size[1] = height;

        screen = SDL_CreateWindow("Cpp Game Dev", xpos, ypos, this->screen_size[0], this->screen_size[1], flags); if (screen) {
            std::clog << "Window created sucessfully!\n" ;
        } else { std::cerr << "WINDOW INITIALIZATION FAILED!\n"; }

        display = SDL_CreateRenderer(screen, -1, 0); if (display) {
            std::clog << "Redereer (Display) created sucessfully!\n";
            
            SDL_SetRenderDrawColor(display, 0, 255, 255, 255);
        } else { std::cerr << "RENDERER (DISPLAY) INITIALIZATION FAILED!\n"; }

        if (assets_init()) {
            std::clog << "Assets initialized!...\n";
        } else { std::cerr << "ASSETS INITIALIZATION FAILED!\n"; }

        this->isRunning = true;
    } else { std::cerr << "SDL2 INITIALIZATION FAILED!\n";
        this->isRunning = false;
    }

    this->player = new PhysicsEntities("player",pos,pos,"");
}


bool Game::handleEvents() {
    SDL_Event event;    
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->isRunning = false;
                return false;
            
            default:
                break;
        }
    }
    return true;
}

void Game::update() {
    this->player->update();
}

void Game::render() {
    SDL_RenderClear(display);

    this->player->render();

    SDL_RenderPresent(display);
}

void Game::clean() {
    SDL_DestroyWindow(screen);
    SDL_DestroyRenderer(display);
    SDL_Quit();

    std::clog << "Game class cleaned!\n";
}