#include "game.hpp"

Game::Game(){ 

}

Game::~Game() {

}


void Game::init(const char* title, int xpos, int ypos, int widht, int height, bool fullscreen) {
    int flags = 0;

    if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::clog << "SDL2 initialized!...\n";

        screen_size[0] = widht; screen_size[1] = height;

        screen = SDL_CreateWindow("Cpp Game Dev", xpos, ypos, screen_size[0], screen_size[1], flags); if (screen) {
            std::clog << "Window created sucessfully!\n" ;
        } else { std::cerr << "WINDOW INITIALIZATION FAILED!\n"; }

        display = SDL_CreateRenderer(screen, -1, 0); if (display) {
            std::clog << "Redereer (Display) created sucessfully!\n";
            
            SDL_SetRenderDrawColor(display, 0, 255, 255, 255);
        } else { std::cerr << "RENDERER (DISPLAY) INITIALIZATION FAILED!\n"; }

        isRunning = true;
    } else { std::cerr << "SDL2 INITIALIZATION FAILED!\n";
        isRunning = false;
    }

}

bool Game::handleEvents() {
    SDL_Event event;    
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                return false;
            
            default:
                break;
        }
    }
    return true;
}


void Game::update() {

}

void Game::render() {
    SDL_RenderClear(display);


    SDL_RenderPresent(display);
}
void Game::clean() {
    SDL_DestroyWindow(screen);
    SDL_DestroyRenderer(display);
    SDL_Quit();

    std::cout << "Game class cleaned!" << std::endl;
}