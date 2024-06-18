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

#ifndef CPPGAMEDEV_CORE_EDITOR_HPP_
#define CPPGAMEDEV_CORE_EDITOR_HPP_

#include "classes/entities.hpp"
#include "classes/tilemap.hpp"
#include "core/assets.hpp"
#include "core/engine.hpp"
#include "core/imageHandle.hpp"

namespace cppGameDev {

class Editor {
   public:
    Editor() { this->tilemap = new Tilemap(); }
    ~Editor() {
        delete this->tilemap;
        std::clog << "Editor class successfully destroyed!\n";
    }

    /**
     * Processes user input events in the game loop.
     *
     * \returns (bool):
     * true if the game should continue running.
     * false if the game should exit.
     */
    bool handleEvents();

    /**
     * Updates the game state and logic.
     *
     * \returns (void): This function does not return a value.
     */
    void update();

    /**
     * Renders the game state to the screen.
     *
     * \returns (void): This function does not return a value.
     */
    void render();

    /**
     * Checks if the game is currently running.
     * \returns (bool):
     *  true if the game is running.
     *  false if the game has quit.
     */
    bool running() { return this->isRunning; }

    void cameraControl();

    Cord getTilePos();

    Tilemap* tilemap;

   private:
    Uint8 scrollSpeed = 2;
    bool isRunning = true;
    std::pair<int, int> movementX = {0, 0};
    std::pair<int, int> movementY = {0, 0};
    Cord scroll = {0, 0};
    Cord mpos = {0, 0};
    bool clicking = false;
    bool right_clicking = false;
    bool ongrid = true;

    std::vector<std::pair<std::string, std::string>> tile_list = {
        {"grass", "Physical"}};
    Uint8 tile_group = 0;
    Uint8 tile_variant = 0;
};
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_EDITOR_HPP_