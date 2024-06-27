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

#ifndef CPPGAMEDEV_CORE_EDITOR_HPP_
#define CPPGAMEDEV_CORE_EDITOR_HPP_

#include "classes/entities.hpp"
#include "classes/tilemap.hpp"
#include "core/assets.hpp"
#include "core/engine.hpp"
#include "core/imageHandle.hpp"
#include "main/app.hpp"

namespace cppGameDev {

class Editor : public App {
 public:
  Editor();
  ~Editor();

  /**
   * Processes user input events in the game loop.
   *
   * \returns (bool):
   * true if the game should continue running.
   * false if the game should exit.
   */
  bool handleEvents() override;

  /**
   * Updates the game state and logic.
   *
   * \returns (void): This function does not return a value.
   */
  void update() override;

  /**
   * Renders the game state to the screen.
   *
   * \returns (void): This function does not return a value.
   */
  void render() override;

  /**
   * Checks if the game is currently running.
   * \returns (bool):
   *  true if the game is running.
   *  false if the game has quit.
   */
  bool running() override { return this->isRunning; }


 private:
  void cameraControl();

  Cord getTilePos();

  void RenderTilePreview();
  void RenderLayerPreview();

  Tilemap* tilemap;

  Uint8 scrollSpeed;
  bool isRunning;
  Cord4d movement;
  Cord scroll;
  Cord mpos;
  bool clicking;
  bool right_clicking;
  bool ongrid;

  bool control;
  bool shift;
  bool alt;

  std::vector<std::pair<std::string, std::string>> tile_list;
  Uint8 tile_group;
  Uint8 tile_variant;

  Uint8 layer;
};
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_EDITOR_HPP_