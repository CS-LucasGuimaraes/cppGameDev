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