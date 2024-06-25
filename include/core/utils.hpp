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

#ifndef CPPGAMEDEV_CORE_UTILS_HPP_
#define CPPGAMEDEV_CORE_UTILS_HPP_

#include "core/engine.hpp"

namespace cppGameDev {

/**
 * Get the floor of the division;
 * @param a (int) The dividend
 * @param b (int) The divisor
 *
 * @return (int) the floor of the real quotient.
 */
int DivFloor(int a, int b);

/**
 * Get the floor of the division;
 * @param a (int) The dividend
 * @param b (int) The divisor
 *
 * @return (int) the ceil of the real quotient.
 */
int DivCeil(int a, int b);

/**
 * Checks wheter two rectangles are superposed.
 * @param a (SDL_RECT) The first rect that you are checking the collision
 * @param b (SDL_RECT) The second rect that you are checking the collision
 *
 * @return (bool) True if the rects are superposed, false otherwise.
 */
bool CollideRect(SDL_Rect* a, SDL_Rect* b);

}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_UTILS_HPP_