#include "src/game.hpp"

const int screen_size[2] = {800,600};
const bool fullscreen = false;

int main(int argc, char* argv[]){

    Game* game = new Game("cppGameDev", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_size[0], screen_size[1], fullscreen);

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }
    
    game->clean();
    
    return 0;
}