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

#ifndef CPPGAMEDEV_CORE_ENTITIES_HPP_
#define CPPGAMEDEV_CORE_ENTITIES_HPP_

#include "classes/animation.hpp"
#include "core/assets.hpp"
#include "core/engine.hpp"

namespace cppGameDev {

class PhysicsEntities {
   public:
    PhysicsEntities(std::string e_type, SDL_Rect initial_rect, std::string ID) {
        this->type = e_type;
        this->entityRect = initial_rect;
        this->pos.x = this->entityRect.x;
        this->pos.y = this->entityRect.y;
        this->ID = ID;

        this->set_action("idle");
    }
    ~PhysicsEntities() {
        std::clog << "PhysicsEntities class (" << this->type << ':' << this->ID
                  << ") successfully destroyed!\n";
    }

    /**
     * Updates the physics entity's internal state.
     *
     * This function updates all the physics entity's state and logic.
     *
     * @returns (void): This function does not return a value.
     */
    void update(int movement = 0);

    /**
     *  Render the entity's animation onto the cppGameDev::renderer surface.
     *
     * \returns (void): This function does not return a value.
     */
    void render();

   private:
    std::string type;
    std::string ID;
    std::string action = "";
    cppGameDev::Speed pos;
    cppGameDev::Speed speed = {0.0, 0.0};
    cppGameDev::RGB color_mod = {255, 255, 255};
    Animation *animation;
    SDL_Rect entityRect;
    std::map<std::string, bool> collisions;
    bool flip = false;

    /**
     * Sets the action of the physics entity.
     *
     * This function updates the action of the physics entity and assigns the
     * corresponding animation.
     *
     * @param action (std::string): The new action to be set for the physics
     * entity.
     *
     * @returns (void): This function does not return a value.
     */
    void set_action(std::string action);

    void reset_collisions();
    void movement_and_collide(int movement);
    void movement_physics();
    void facing_side(int movement);
};
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_ENTITIES_HPP_