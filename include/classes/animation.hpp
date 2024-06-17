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

#ifndef CPPGAMEDEV_CORE_ANIMATION_HPP_
#define CPPGAMEDEV_CORE_ANIMATION_HPP_

#include "core/engine.hpp"

namespace cppGameDev {

class Animation {
   public:
    Animation(const std::vector<__SDL_Texture> imgs, int img_dur = 5,
              bool loop = true) {
        this->images = imgs;
        this->img_duration = img_dur;
        this->is_looping = loop;
        this->done = false;
        this->frame = 0;
    }
    ~Animation() {
        std::clog << "Animation class successfully destroyed!\n";
        ;
    }

    /**
     * Updates the animation frame.
     *
     * \returns (void): This function does not return a value.
     *
     */
    void update();

    /**
     * Get the image that represents the current frame.
     *
     * \returns (__SDL_Texture *):
     * The image that represents the frame.
     *
     */
    __SDL_Texture img();

    std::vector<__SDL_Texture>* img_list();

   private:
    std::vector<__SDL_Texture> images;
    int img_duration;
    bool is_looping;
    bool done;
    int frame;
};
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_ANIMATION_HPP_