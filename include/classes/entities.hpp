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
#include "classes/tilemap.hpp"
#include "core/assets.hpp"
#include "core/engine.hpp"

namespace cppGameDev {

struct Collisions {
    bool up;
    bool down;
    bool left;
    bool right;
};

class PhysicsEntities {
   public:
    PhysicsEntities(std::string e_type, SDL_Rect initial_rect, std::string ID,
                    Tilemap* tilemap);
    virtual ~PhysicsEntities();

    /**
     * Updates the physics entity's internal state.
     *
     * This function updates all the physics entity's state and logic.
     *
     * @returns (void): This function does not return a value.
     */
    virtual void update(int movement = 0);

    /**
     *  Render the entity's animation onto the cppGameDev::renderer surface.
     *
     * \returns (void): This function does not return a value.
     */
    virtual void render();

   protected:
    std::string type;
    std::string ID;
    std::string action = "";
    cppGameDev::Speed pos;
    cppGameDev::Speed speed = {0.0, 0.0};
    cppGameDev::RGB color_mod = {255, 255, 255};
    Tilemap* tilemap;
    Animation* animation;
    SDL_Rect entityRect;
    Collisions collisions;
    bool flip = false;
    std::map<std::string, std::function<void(Speed, SDL_Rect*)>> collide;

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

    Cord getPos();

    void reset_collisions();
    void movement_and_collide(int movement);
    void movement_physics();
    void facing_side(int movement);

    void defCollisions();
};

class Player : public PhysicsEntities {
   public:
    Player(std::string e_type, SDL_Rect initial_rect, std::string ID,
           Tilemap* tilemap);
    ~Player();

    virtual void update(int movement) override;
    void Jump();

   protected:
    int max_jumps;
    int jumps;
    int air_time;
    bool in_air;

    void JumpControl();
    void WallJump();
};

}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_ENTITIES_HPP_