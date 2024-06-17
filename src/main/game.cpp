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

#include "main/game.hpp"

namespace cppGameDev {

bool Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->isRunning = false;
                return false;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        this->movement.first = 1;
                        break;

                    case SDLK_d:
                        this->movement.second = 1;
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        this->movement.first = 0;
                        break;

                    case SDLK_d:
                        this->movement.second = 0;
                        break;
                }
                break;
        }
    }
    return true;
}

void Game::update() {
    this->player->update(this->movement.second - this->movement.first);
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