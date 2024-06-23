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

#include "main/game.hpp"

namespace cppGameDev {

Game::Game() {
    this->tilemap = new Tilemap();
    this->player = new Player({21, 21, 128, 128}, {64-7,64-11,14,22}, "", this->tilemap);
}

Game::~Game() {
    delete this->player;
    delete this->tilemap;
    std::clog << "Game class successfully destroyed!\n";
}

bool Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->isRunning = false;
                return false;

            case SDL_KEYDOWN:
                if (assets::keybinds["LEFT"].count(event.key.keysym.sym)) {
                    this->movement.l = 1;
                } else if (assets::keybinds["RIGHT"].count(
                               event.key.keysym.sym)) {
                    this->movement.r = 1;
                } else if (assets::keybinds["UP"].count(
                               event.key.keysym.sym)) {
                    this->movement.u = 1;
                } else if (assets::keybinds["DOWN"].count(
                               event.key.keysym.sym)) {
                    this->movement.d = 1;
                }

                break;

            case SDL_KEYUP:
                if (assets::keybinds["LEFT"].count(event.key.keysym.sym)) {
                    this->movement.l = 0;
                } else if (assets::keybinds["RIGHT"].count(
                               event.key.keysym.sym)) {
                    this->movement.r = 0;
                } else if (assets::keybinds["UP"].count(
                               event.key.keysym.sym)) {
                    this->movement.u = 0;
                } else if (assets::keybinds["DOWN"].count(
                               event.key.keysym.sym)) {
                    this->movement.d = 0;
                }

                break;
        }
    }
    return true;
}

void Game::update() {
    this->player->update(this->movement);
}

void Game::render() {
    SDL_SetRenderTarget(renderer, display);
    SDL_RenderClear(renderer);

    this->player->render();
    this->tilemap->render({0, 0});

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, display, NULL, NULL);

    SDL_RenderPresent(renderer);
}
}  // namespace cppGameDev