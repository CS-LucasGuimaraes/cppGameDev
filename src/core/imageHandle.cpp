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

#include "core/imageHandle.hpp"

namespace cppGameDev {

std::string BASE_PATH = "../assets/images/";

__SDL_Texture load_image(const char* path) {
    return IMG_LoadTexture(cppGameDev::renderer, path);
}

const std::vector<__SDL_Texture> load_images(const char* path) {
    std::vector<__SDL_Texture> images;
    for (auto const& file :
         std::filesystem::directory_iterator((BASE_PATH + path).c_str())) {
        images.push_back(load_image((BASE_PATH + std::string(path) + "/" +
                                     file.path().filename().string())
                                        .c_str()));
        std::clog << "    " << std::string(path) << "/"
                  << file.path().filename().string() << " loaded.\n";
    }

    return images;
}
}  // namespace cppGameDev