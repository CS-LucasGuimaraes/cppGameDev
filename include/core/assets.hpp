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

#ifndef CPPGAMEDEV_CORE_ASSETS_HPP_
#define CPPGAMEDEV_CORE_ASSETS_HPP_

#include "classes/animation.hpp"
#include "engine.hpp"
#include "imageHandle.hpp"

namespace cppGameDev {
namespace assets {

extern std::map<std::string, Animation*> animations;
extern std::map<std::string, std::vector<__SDL_Texture>> tiles;

/**
 * Initializes the game assets.
 *
 * This function loads and stores animation data for different player states.
 *
 * @returns (bool): This function returns true on success, or false on failure
 * (e.g., loading errors).
 */
bool init();

}  // namespace assets
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_ASSETS_HPP_