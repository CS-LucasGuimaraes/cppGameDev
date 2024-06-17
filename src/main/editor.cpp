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

#include "main/editor.hpp"

namespace cppGameDev {

bool Editor::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->isRunning = false;
                return false;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        this->movementX.first = 1;
                        break;

                    case SDLK_d:
                        this->movementX.second = 1;
                        break;

                    case SDLK_w:
                        this->movementY.first = 1;
                        break;

                    case SDLK_s:
                        this->movementY.second = 1;
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        this->movementX.first = 0;
                        break;

                    case SDLK_d:
                        this->movementX.second = 0;
                        break;

                    case SDLK_w:
                        this->movementY.first = 0;
                        break;

                    case SDLK_s:
                        this->movementY.second = 0;
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&this->mpos.x, &this->mpos.y);

                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        this->clicking = true;
                        break;

                    case SDL_BUTTON_RIGHT:
                        this->right_clicking = true;
                        break;

                    case SDL_BUTTON_MIDDLE:

                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        this->clicking = false;
                        break;

                    case SDL_BUTTON_RIGHT:
                        this->right_clicking = false;
                        break;

                    case SDL_BUTTON_MIDDLE:

                        break;
                }
                break;
        }
    }
    return true;
}

void Editor::update() {
    this->cameraControl();

    if (this->ongrid) {
        Cord tilepos = this->getTilePos();
        std::string tile_loc =
            std::to_string(tilepos.x) + ";" + std::to_string(tilepos.y);

        if (this->clicking) {
            this->tilemap->tilemap[tile_loc] = {
                this->tile_list[this->tile_group].first, this->tile_variant,
                tilepos, this->tile_list[this->tile_group].second};
        }

        if (this->right_clicking) {
            if (this->tilemap->tilemap.count(tile_loc) != 0) {
                this->tilemap->tilemap.erase(tile_loc);
            }
        }
    }

    else {
    }
}

void Editor::render() {
    SDL_SetRenderTarget(renderer, display);
    SDL_RenderClear(renderer);

    this->tilemap->render(this->scroll);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, display, NULL, NULL);

    SDL_RenderPresent(renderer);
}

void Editor::cameraControl() {
    this->scroll.x +=
        (this->movementX.second - this->movementX.first) * this->scrollSpeed;
    this->scroll.y +=
        (this->movementY.second - this->movementY.first) * this->scrollSpeed;
}

Cord Editor::getTilePos() {
    return {(int)std::floor((((float)this->mpos.x / (float)kRenderScale) +
                             (float)this->scroll.x) /
                            (float)this->tilemap->tile_size),
            (int)std::floor((((float)this->mpos.y / (float)kRenderScale) +
                             (float)this->scroll.y) /
                            (float)this->tilemap->tile_size)};
}
}  // namespace cppGameDev