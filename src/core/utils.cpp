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

#include "core/utils.hpp"

namespace cppGameDev {

int DivFloor(int a, int b) { return (int)std::floor((float)a / (float)b); }

int DivCeil(int a, int b) { return (int)std::ceil((float)a / (float)b); }

bool CollideRect(SDL_Rect* a, SDL_Rect* b) {
    if (((a->x + a->w > b->x) && (a->x < b->x + b->w)) &&
        ((a->y + a->h > b->y) && (a->y < b->y + b->h))) {
        return true;
    }
    return false;
}

}  // namespace cppGameDev