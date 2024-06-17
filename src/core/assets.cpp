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

#include "core/assets.hpp"

namespace cppGameDev {
namespace assets {

std::map<std::string, Animation*> animations;
std::map<std::string, std::vector<__SDL_Texture>> tiles;

bool init() {
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