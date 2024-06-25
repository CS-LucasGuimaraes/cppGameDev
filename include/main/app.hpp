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

#ifndef CPPGAMEDEV_CORE_APP_HPP_
#define CPPGAMEDEV_CORE_APP_HPP_

namespace cppGameDev {

class App {
 public:
  virtual ~App(){};

  /**
   * Processes user input events in the game loop.
   *
   * \returns (bool):
   * true if the game should continue running.
   * false if the game should exit.
   */
  virtual bool handleEvents() = 0;

  /**
   * Updates the game state and logic.
   *
   * \returns (void): This function does not return a value.
   */
  virtual void update() = 0;

  /**
   * Renders the game state to the screen.
   *
   * \returns (void): This function does not return a value.
   */
  virtual void render() = 0;

  /**
   * Checks if the game is currently running.
   * \returns (bool):
   *  true if the game is running.
   *  false if the game has quit.
   */
  virtual bool running() = 0;
};
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_APP_HPP_