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

#include "core/assets.hpp"

namespace cppGameDev {
namespace assets {

std::map<std::string, std::unordered_set<int>> keybinds;
std::map<std::string, Animation *> animations;
std::map<std::string, std::vector<SDL_Texture *>> tiles;

bool init() {
    keybinds = { 
                {"LEFT", {SDLK_a, SDLK_LEFT} },
                {"RIGHT", {SDLK_d, SDLK_RIGHT} },
                {"JUMP", {SDLK_w, SDLK_UP, SDLK_SPACE} }
            };

    animations = {
        {"player/idle", new Animation(load_images("entities/player/idle"), 16)},
    };

    tiles = {
        {"grass", load_images("tiles/grass")},
    };

    return true;
}

}  // namespace assets
}  // namespace cppGameDev