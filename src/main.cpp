//    Copyright 2024 Lucas Guimarães Fernandes
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#include "core/engine.hpp"
#include "main/app.hpp"
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

    App* app = nullptr;
    int mode;
    do {
        std::cout << "[0] exit\n"
                  << "[1] game\n"
                  << "[2] editor\n";
        std::cin >> mode;

        if (mode == 1) {
            app = new Game();
        } else if (mode == 2) {
            app = new Editor();
        }

        while (app->running()) {
            frameStart = SDL_GetTicks64();

            app->handleEvents();
            app->update();
            app->render();

            processingTime = SDL_GetTicks64() - frameStart;

            if (frameSize > processingTime) {
                SDL_Delay(frameSize - processingTime);
                std::clog << processingTime * 100 / frameSize << '\n';
            } else {
                std::cerr << "[WARNING!] GAME IS " << processingTime - frameSize
                          << "ms DELAYED.\n";
            }
        }
        delete app;

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    } while (mode != 0);

    Shutdown();

    return 0;
}