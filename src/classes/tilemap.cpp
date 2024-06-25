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

#include "classes/tilemap.hpp"

namespace cppGameDev {

// public:

void Tilemap::render(Cord offset) {
  std::map<std::string, tile>::iterator tile;

  for (int x = DivFloor(offset.x, this->tile_size);
       x < DivFloor(offset.x + kDisplaySize.x, this->tile_size) + 1; x++) {
    for (int y = DivFloor(offset.y, this->tile_size);
         y < DivFloor(offset.y + kDisplaySize.y, this->tile_size) + 1; y++) {
      std::string loc = std::to_string(x) + ';' + std::to_string(y);
      if ((tile = this->tilemap.find(loc)) != this->tilemap.end()) {
        if (tile->second.category == "ANIMATION") {
          this->dstR.x = x * this->tile_size - offset.x;
          this->dstR.y = y * this->tile_size - offset.y;
          // SDL_RenderCopy(renderer,
          // tile->second.animation->img(), NULL, &this->dstR);
        }

        else if (tile->second.category == "EDITOR_ONLY") {
          //
        }

        else {
          this->dstR.x = x * this->tile_size - offset.x;
          this->dstR.y = y * this->tile_size - offset.y;
          SDL_RenderCopy(renderer,
                         assets::tiles[tile->second.type][tile->second.variant],
                         NULL, &this->dstR);
        }
      }
    }
  }
}

std::vector<tile*> Tilemap::tiles_around(Cord pos) {
  std::vector<tile*> tiles;
  std::map<std::string, tile>::iterator tile;
  Cord tile_loc = {pos.x / this->tile_size, pos.y / this->tile_size};

  for (auto offset : tilemap::NEIGHBOR_OFFSETS) {
    std::string loc = std::to_string(tile_loc.x + offset.x) + ';' +
                      std::to_string(tile_loc.y + offset.y);
    if ((tile = this->tilemap.find(loc)) != this->tilemap.end()) {
      tiles.push_back(&tile->second);
    }
  }

  return tiles;
}

void Tilemap::load() {
  int level = 0;
  std::ifstream f("../assets/levels/level" + std::to_string(level) + ".json");
  nlohmann::json data = nlohmann::json::parse(f);

  for (auto [k, v] : data.items()) {
    this->tilemap[k] = {
        v["type"], v["variant"], {v["pos"][0], v["pos"][1]}, v["category"]};
  }
}

void Tilemap::save() {
  int level = 0;
  std::ofstream out("../assets/levels/level" + std::to_string(level) + ".json");

  nlohmann::json j;

  for (auto [k, v] : this->tilemap) {
    j[k] = {{"type", v.type},
            {"variant", v.variant},
            {"pos", {v.pos.x, v.pos.y}},
            {"category", v.category}};
  }
  out << j;
}
}  // namespace cppGameDev