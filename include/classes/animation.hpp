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

#ifndef CPPGAMEDEV_CORE_ANIMATION_HPP_
#define CPPGAMEDEV_CORE_ANIMATION_HPP_

#include "core/engine.hpp"

namespace cppGameDev {

class Animation {
 public:
  /**
   * Constructor for the Animation class.
   *
   * \param imgs (const std::vector<SDL_Texture *>): The vector of SDL textures
   * representing the frames of the animation. \param img_dur (int): The
   * duration (in frames) for each image in the animation. \param loop (bool):
   * Flag indicating whether the animation should loop or not.
   */
  Animation(const std::vector<SDL_Texture *> imgs, int img_dur = 5,
            bool loop = true);

  /**
   * Destructor for the Animation class.
   */
  ~Animation();

  /**
   * Updates the animation frame.
   *
   * \returns (void): This function does not return a value.
   */
  void update();

  /**
   * Get the image that represents the current frame.
   *
   * \returns (SDL_Texture *): The image that represents the frame.
   */
  SDL_Texture *img();

  /**
   * Get the list of images used in the animation.
   *
   * \returns (std::vector<SDL_Texture *> *): A pointer to the vector of SDL
   * textures representing the frames of the animation.
   */
  std::vector<SDL_Texture *> *img_list();

 private:
  std::vector<SDL_Texture *> images;  // The vector of SDL textures representing
                                      // the frames of the animation.
  int img_duration;  // The duration (in frames) for each image in the
                     // animation.
  bool is_looping;  // Flag indicating whether the animation should loop or not.
  bool done;  // Flag indicating whether the animation has finished playing.
  int frame;  // The current frame of the animation.
};
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_ANIMATION_HPP_