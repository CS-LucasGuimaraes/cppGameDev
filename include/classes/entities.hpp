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

/**
 * @class PhysicsEntities
 * @brief Represents a physics-based entity in the game.
 *
 * The PhysicsEntities class is a base class for all physics-based entities
 * in the game. It provides common functionality and properties for entities
 * that interact with the game's physics system.
 */
class PhysicsEntities {
 public:
  /**
   * @brief Constructs a PhysicsEntities object.
   *
   * This constructor initializes a PhysicsEntities object with the specified
   * parameters.
   *
   * @param e_type The type of the entity.
   * @param initial_rect The initial position and size of the entity.
   * @param hitbox The hitbox of the entity.
   * @param ID The ID of the entity.
   * @param tilemap A pointer to the tilemap object.
   */
  PhysicsEntities(std::string e_type, SDL_Rect initial_rect, SDL_Rect hitbox,
                  std::string ID, Tilemap* tilemap);

  /**
   * @brief Destroys the PhysicsEntities object.
   *
   * This destructor is responsible for cleaning up any resources used by the
   * PhysicsEntities object.
   */
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
  virtual void render(Cord offset);

  /**
   * @brief Get the rectangle representing the entity's position and size.
   * 
   * @return The SDL_Rect representing the entity's position and size.
   */
  SDL_Rect getEntityRect() { return this->entityRect; }

 protected:
  float current_speed;       /**< The current speed of the entity. */
  std::string type;        /**< The type of the entity. */
  std::string ID;          /**< The ID of the entity. */
  std::string action = ""; /**< The current action of the entity. */
  cppGameDev::Speed pos;   /**< The position of the entity. */
  cppGameDev::RGB color_mod = {255, 255, 255}; /**< The color modifier. */
  Tilemap* tilemap;        /**< A pointer to the tilemap object. */
  Animation* animation;    /**< The animation of the entity. */
  SDL_Rect entityRect;     /**< Rect representing entity's position and size. */
  SDL_Rect hitbox;         /**< The hitbox of the entity. */
  SDL_Rect hitbox_mod;     /**< Th hitbox modifier of the entity. */
  Collisions collisions;   /**< The collisions of the entity.*/
  std::string side;        /**< The side that the entity should look. */
  std::string setted_side; /**< The side that the entity is really looking. */
  std::map<std::string, std::function<void(Speed, SDL_Rect*)>>
      collide; /**< The collision functions of the entity. */
  Uint8 layer; /**< The layer where the entity currently is. */

  /**
   * @brief Sets the action for the entity.
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

  /**
   * @brief Defines the collision functions for the entity.
   */
  void defCollisions();

  /**
   * @brief Controls the actions of the entity.
   *
   * @param movement The movement vector of the entity.
   */
  void ControlActions(Cord4d movement);

  /**
   * @brief Gets the movement vector for the current frame.
   *
   * @param movement The movement vector of the entity.
   * @return The movement vector for the current frame.
   */
  Speed getFrameMovement(Cord4d movement);

  /**
   * @brief Updates the hitbox position along the X-axis.
   */
  void updateHitboxX();

  /**
   * @brief Updates the hitbox position along the Y-axis.
   */
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