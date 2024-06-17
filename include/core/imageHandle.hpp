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

#ifndef CPPGAMEDEV_CORE_IMAGEHANDLE_HPP_
#define CPPGAMEDEV_CORE_IMAGEHANDLE_HPP_

#include "core/engine.hpp"

namespace cppGameDev {

extern std::string BASE_PATH;

/**
 * Create a texture from an image file using the class surface as base.
 *
 * \param path a path on the filesystem to load an image from.
 * \returns the created texture or NULL on failure; call SDL_GetError() for more
 * information.
 */
__SDL_Texture load_image(const char* path);

/**
 * Create a list of textures from a folder path.
 *
 * \param path a path on the filesystem to the folder you want to load the
 * images from. \returns a vector with the created textures or NULL on failure;
 */
const std::vector<__SDL_Texture> load_images(const char* path);

}  // namespace cppGameDev

#endif // CPPGAMEDEV_CORE_IMAGEHANDLE_HPP_