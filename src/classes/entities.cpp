//    Copyright 2024 Lucas Guimarães Fernandes
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

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