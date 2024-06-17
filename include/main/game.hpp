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

#ifndef CPPGAMEDEV_CORE_GAME_HPP_
#define CPPGAMEDEV_CORE_GAME_HPP_

#include "classes/entities.hpp"
#include "classes/tilemap.hpp"
#include "core/assets.hpp"
#include "core/engine.hpp"
#include "core/imageHandle.hpp"

namespace cppGameDev {

class Game {
   public:
    Game() {
        this->player = new PhysicsEntities("player", {21, 21, 64, 64}, "");
        this->tilemap = new Tilemap();
    }
    ~Game() {
        delete this->player;
        std::clog << "Game class successfully destroyed!\n";
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

   private:
    bool isRunning = true;
    PhysicsEntities* player;
    Tilemap* tilemap;
    std::pair<int, int> movement = {0, 0};
};
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_GAME_HPP_