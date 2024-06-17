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