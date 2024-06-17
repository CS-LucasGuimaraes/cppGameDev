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

#include "classes/entities.hpp"

namespace cppGameDev {

// public:

void PhysicsEntities::update(int movement) {
    this->reset_collisions();
    this->movement_and_collide(movement);
    this->movement_physics();
    this->facing_side(movement);
    this->animation->update();
}

void PhysicsEntities::render() {
    if (this->flip)
        SDL_RenderCopyEx(renderer, this->animation->img(), NULL,
                         &this->entityRect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopy(renderer, this->animation->img(), NULL,
                       &this->entityRect);
}

// private:

void PhysicsEntities::set_action(std::string action) {
    if (action != this->action) {
        this->action = action;
        this->animation =
            assets::animations[this->type + this->ID + '/' + this->action];

        for (auto img : *this->animation->img_list()) {
            SDL_SetTextureColorMod(img, this->color_mod.r, this->color_mod.g,
                                   this->color_mod.b);
        }
    }
}

void PhysicsEntities::reset_collisions() {
    this->collisions = {
        {"up", false}, {"down", false}, {"right", false}, {"left", false}};
}

void PhysicsEntities::movement_and_collide(int movement) {
    this->pos.x += movement + this->speed.x;
    this->entityRect.x = this->pos.x;

    // x collisions

    this->pos.y += this->speed.y;
    this->entityRect.y = this->pos.y;

    // y collisions
}

void PhysicsEntities::movement_physics() {
    // this->speed.y = std::min(5.0, this->speed.y + 0.1); // Gravity

    if (this->speed.x > 0) {
        this->speed.x = std::max(this->speed.x - 0.1, 0.0);  // Right slowdown
    } else if (this->speed.x < 0) {
        this->speed.x = std::min(this->speed.x + 0.1, 0.0);  // Left slowdown
    }

    if (this->collisions["down"] || this->collisions["up"]) {
        this->speed.y = 0;
    }
}

void PhysicsEntities::facing_side(int movement) {
    if (movement + this->speed.x > 0) {
        this->flip = false;
    } else if (movement + this->speed.x < 0) {
        this->flip = true;
    }
}
}  // namespace cppGameDev