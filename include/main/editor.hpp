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