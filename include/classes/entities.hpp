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
  PhysicsEntities(std::string e_type, SDL_Rect initial_rect, SDL_Rect hitbox,
                  std::string ID, Tilemap* tilemap);
  virtual ~PhysicsEntities();

  /**
   * @brief Updates the entity's position based on the given movement.
   *
   * This function is called to update the position of the entity based on the
   * provided movement. The movement is specified using a `Cord4d` object,
   * which represents the movement in 4-dimensional space.
   *
   * @param movement The movement to apply to the entity's position.
   */
  virtual void update(Cord4d movement);

  /**
   * @brief Renders the entity.
   *
   * This function is called to render the entity on the screen.
   */
  virtual void render();

 protected:
  int current_speed;
  std::string type;
  std::string ID;
  std::string action = "";
  cppGameDev::Speed pos;
  cppGameDev::RGB color_mod = {255, 255, 255};
  Tilemap* tilemap;
  Animation* animation;
  SDL_Rect entityRect;
  SDL_Rect hitbox;
  SDL_Rect hitbox_mod;
  Collisions collisions;
  std::string side;
  std::string setted_side;
  std::map<std::string, std::function<void(Speed, SDL_Rect*)>> collide;
  Uint8 layer;

  /**
   * Sets the action for the entity.
   *
   * @param action The action to set.
   */
  void set_action(std::string action);

  /**
   * @brief Retrieves the position of the entity.
   *
   * @return The position of the entity as a Cord object.
   */
  Cord getPos();

  /**
   * @brief Resets the collision state of the entity.
   *
   * This function resets the collision state of the entity, allowing it to
   * detect collisions again.
   *
   * @note This function does not modify the position or other properties of
   * the entity.
   */
  void reset_collisions();

  /**
   * @brief Moves the entity and checks for collisions.
   *
   * This function moves the entity according to the movement vector and
   * checks for collisions with the tilemap.
   *
   * @param movement The movement vector to apply to the entity.
   */
  void movement_and_collide(Cord4d movement);

  /**
   * @brief Sets the facing side of the entity.
   *
   * This function sets the facing side of the entity based on the movement
   * vector.
   *
   * @param movement The movement vector to use to determine the facing side.
   */
  void facing_side(Cord4d movement);

  void defCollisions();

  void ControlActions(Cord4d movement);

  Speed getFrameMovement(Cord4d movement);

  void updateHitbox();
  void updateHitboxX();
  void updateHitboxY();
};

class Player : public PhysicsEntities {
 public:
  Player(SDL_Rect initial_rect, SDL_Rect hitbox, std::string ID,
         Tilemap* tilemap);
  ~Player();

  virtual void update(Cord4d movement) override;

 protected:
};

}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_ENTITIES_HPP_