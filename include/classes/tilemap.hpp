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

#ifndef CPPGAMEDEV_CORE_TILEMAP_HPP_
#define CPPGAMEDEV_CORE_TILEMAP_HPP_

#include "classes/animation.hpp"
#include "core/assets.hpp"
#include "core/engine.hpp"
#include "core/utils.hpp"

namespace cppGameDev {
struct tile {
    std::string type;
    uint8_t variant;
    Cord pos;
    std::string category;
};

namespace tilemap {
const Cord NEIGHBOR_OFFSETS[9] = {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {0, 0},
                                  {1, 0},  {-1, -1}, {0, -1}, {1, -1}};
}  // namespace tilemap

class Tilemap {
   public:
    int tile_size = 32;

    Tilemap() {
        this->load();

        this->dstR.h = this->tile_size;
        this->dstR.w = this->tile_size;
    }
    ~Tilemap() { this->save(); }

    /**
     *  Render the tilemap onto the renderer surface.
     *
     * \returns (void): This function does not return a value.
     */
    void render(Cord offset);

    std::vector<tile*> tiles_around(Cord pos);

    void load();

    void save();

    std::map<std::string, tile> tilemap;

   private:
    SDL_Rect dstR;
};
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_TILEMAP_HPP_