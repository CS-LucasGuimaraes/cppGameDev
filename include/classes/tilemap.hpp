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