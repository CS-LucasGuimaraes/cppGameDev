// Copyright (C) 2024 Lucas Guimarães
// 
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
// 
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "core/engine.hpp"
#include "main/editor.hpp"
#include "main/game.hpp"

const bool kFullscreen = false;

using namespace cppGameDev;

int main(int argc, char* argv[]) {
    const int refreshRate = 60;
    const int frameSize = 1000 / refreshRate;

    Uint64 frameStart;
    Uint64 processingTime;

    Init("cppGameDev",
         {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kScreenSize.x,
          kScreenSize.y},
         kFullscreen);

    if (assets::init()) {
        std::clog << "Assets initialized!...\n";
    } else {
        std::cerr << "[WARNING!] ASSETS INITIALIZATION FAILED!\n";
    }

    int mode = 2;
    do {
        std::cout << "[0] exit\n[1] game\n[2] editor\n";
        std::cin >> mode;

        if (mode == 1) {
            Game* game = new Game();
            while (game->running()) {
                frameStart = SDL_GetTicks64();

                game->handleEvents();
                game->update();
                game->render();

                processingTime = SDL_GetTicks64() - frameStart;

                if (frameSize > processingTime) {
                    SDL_Delay(frameSize - processingTime);
                    // std::clog << frameSize-processingTime << '\n';
                } else {
                    std::cerr << "[WARNING!] GAME IS "
                              << processingTime - frameSize << "ms DELAYED.\n";
                }
            }
            delete game;
        } else if (mode == 2) {
            Editor* editor = new Editor();
            while (editor->running()) {
                frameStart = SDL_GetTicks64();

                editor->handleEvents();
                editor->update();
                editor->render();

                processingTime = SDL_GetTicks64() - frameStart;

                if (frameSize > processingTime) {
                    SDL_Delay(frameSize - processingTime);
                    // std::clog << frameSize-processingTime << '\n';
                } else {
                    std::cerr << "[WARNING!] GAME IS "
                              << processingTime - frameSize << "ms DELAYED.\n";
                }
            }
            delete editor;
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

    } while (mode != 0);

    Shutdown();

    return 0;
}