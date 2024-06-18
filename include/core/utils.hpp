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