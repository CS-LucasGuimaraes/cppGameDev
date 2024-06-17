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

#include "classes/animation.hpp"

namespace cppGameDev {

void Animation::update() {
    if (this->is_looping) {
        this->frame =
            (this->frame + 1) % (this->img_duration * this->images.size());
    } else {
        this->frame =
            std::min(int(this->frame + 1),
                     int(this->img_duration * this->images.size() - 1));
        if (this->frame >= int(this->img_duration * this->images.size() - 1)) {
            this->done = true;
        }
    }
}

__SDL_Texture Animation::img() {
    return this->images[size_t(this->frame / this->img_duration)];
}

std::vector<__SDL_Texture>* Animation::img_list() { return &this->images; }
}  // namespace cppGameDev