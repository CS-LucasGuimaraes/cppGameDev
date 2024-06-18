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

namespace cppGameDev {

SDL_Window *screen = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *display = nullptr;

const Cord kDisplaySize = {640, 360};
const Cord kScreenSize = {1280, 720};
const int kRenderScale = kScreenSize.x / kDisplaySize.x;

bool Init(const char *title, SDL_Rect window_features, bool fullscreen) {
    Uint32 flags = 0;

    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0) {
        std::clog << "SDL2 initialized!...\n";

        screen = SDL_CreateWindow("Cpp Game Dev", window_features.x,
                                  window_features.y, window_features.w,
                                  window_features.h, flags);
        if (screen) {
            std::clog << "Window created sucessfully!\n";
        } else {
            std::cerr << "[WARNING!] WINDOW INITIALIZATION FAILED!\n"
                      << "     [SDL]: " << SDL_GetError() << '\n';
        }

        renderer = SDL_CreateRenderer(screen, -1, 0);
        if (renderer) {
            std::clog << "Redereer created sucessfully!\n";

            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        } else {
            std::cerr << "[WARNING!] RENDERER INITIALIZATION FAILED!\n"
                      << "     [SDL]: " << SDL_GetError() << '\n';
        }

        display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, kDisplaySize.x,
                                    kDisplaySize.y);
        if (display) {
            std::clog << "Display (render target) created sucessfully!\n";

        } else {
            std::cerr
                << "[WARNING!] DISPLAY (RENDER TARGET) INITIALIZATION FAILED!\n"
                << "     [SDL]: " << SDL_GetError() << '\n';
        }

        return true;
    } else {
        std::cerr << "[WARNING!] SDL2 INITIALIZATION FAILED!\n";
        return false;
    }
}

void Shutdown() {
    SDL_DestroyWindow(screen);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::clog << "Engine shutdown sucessfully!\n";
}
}  // namespace cppGameDev