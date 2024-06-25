//  Copyright 2024 Lucas Guimarães Fernandes
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include "core/assets.hpp"

namespace cppGameDev {
namespace assets {

std::map<std::string, std::unordered_set<int>> keybinds;
std::map<std::string, Animation *> animations;
std::map<std::string, std::vector<SDL_Texture *>> tiles;
std::map<std::string, std::vector<SDL_Texture *>> ui;

bool init() {
  keybinds = {
      {"LEFT", {SDLK_a, SDLK_LEFT} },
      {"RIGHT", {SDLK_d, SDLK_RIGHT} },
      {"UP", {SDLK_w, SDLK_UP} },
      {"DOWN", {SDLK_s, SDLK_DOWN} },
  };

  animations = {
      {"player/left/idle",
       new Animation(load_images("entities/player/left/idle"), 5)},
      {"player/right/idle",
       new Animation(load_images("entities/player/right/idle"), 5)},
      {"player/down/idle",
       new Animation(load_images("entities/player/down/idle"), 5)},
      {"player/up/idle",
       new Animation(load_images("entities/player/up/idle"), 5)},

      {"player/left/run",
       new Animation(load_images("entities/player/left/run"), 5)},
      {"player/right/run",
       new Animation(load_images("entities/player/right/run"), 5)},
      {"player/down/run",
       new Animation(load_images("entities/player/down/run"), 5)},
      {"player/up/run",
       new Animation(load_images("entities/player/up/run"), 5)},
  };

  tiles = {
      {"grass", load_images("tiles/grass")},
  };

  ui = {
      {"border", load_images("ui/border")},
  };

  return true;
}

}  // namespace assets
}  // namespace cppGameDev