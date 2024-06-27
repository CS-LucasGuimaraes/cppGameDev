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

Tilemap::Tilemap() {
  this->tilemap = std::vector<std::map<std::string, tile>>(
      256, std::map<std::string, tile>());

  this->load();

  this->dstR.h = this->tile_size;
  this->dstR.w = this->tile_size;
}
Tilemap::~Tilemap() { this->save(); }

void Tilemap::render(Cord offset) {
  std::map<std::string, tile>::iterator tile;

  for (int i : this->layers) {
    for (int x = DivFloor(offset.x, this->tile_size);
         x < DivFloor(offset.x + kDisplaySize.x, this->tile_size) + 1; x++) {
      for (int y = DivFloor(offset.y, this->tile_size);
           y < DivFloor(offset.y + kDisplaySize.y, this->tile_size) + 1; y++) {
        std::string loc = std::to_string(x) + ';' + std::to_string(y);
        if ((tile = this->tilemap[i].find(loc)) != this->tilemap[i].end()) {
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
            SDL_RenderCopy(
                renderer,
                assets::tiles[tile->second.type][tile->second.variant], NULL,
                &this->dstR);
          }
        }
      }
    }
  }
}

std::vector<tile*> Tilemap::tiles_around(Cord pos, Uint8 layer) {
  std::vector<tile*> tiles;
  std::map<std::string, tile>::iterator tile;
  Cord tile_loc = {pos.x / this->tile_size, pos.y / this->tile_size};

  for (auto offset : tilemap::NEIGHBOR_OFFSETS) {
    std::string loc = std::to_string(tile_loc.x + offset.x) + ';' +
                      std::to_string(tile_loc.y + offset.y);
    if ((tile = this->tilemap[layer].find(loc)) != this->tilemap[layer].end()) {
      tiles.push_back(&tile->second);
    }
  }

  return tiles;
}

void Tilemap::load() {
  this->layers.clear();
  this->tilemap.clear();

  int level = 0;
  std::ifstream f("../assets/levels/level" + std::to_string(level) + ".json");
  if (f.peek() == std::ifstream::traits_type::eof()) return;
  nlohmann::json data = nlohmann::json::parse(f);

  this->tile_size = data["tile_size"];

  for (auto [index, tmap] : data["tilemap"].items()) {
    this->layers.insert(std::stoi(index));
    for (auto [k, v] : tmap.items()) {
      this->tilemap[std::stoi(index)][k] = {
          v["type"], v["variant"], {v["pos"][0], v["pos"][1]}, v["category"]};
    }
  }
}

void Tilemap::save() {
  int level = 0;
  std::ofstream out("../assets/levels/level" + std::to_string(level) + ".json");

  nlohmann::json j;

  j["tile_size"] = this->tile_size;

  for (size_t i = 0; i < 256; i++) {
    for (auto [k, v] : this->tilemap[i]) {
      j["tilemap"][std::to_string(i)][k] = {{"type", v.type},
                                            {"variant", v.variant},
                                            {"pos", {v.pos.x, v.pos.y}},
                                            {"category", v.category}};
    }
  }
  out << j;
}
}  // namespace cppGameDev