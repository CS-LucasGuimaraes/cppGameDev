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

#ifndef CPPGAMEDEV_CORE_ENGINE_HPP_
#define CPPGAMEDEV_CORE_ENGINE_HPP_

#include <bits/stdc++.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "nlohmann/json.hpp"
#include "yaml-cpp/yaml.h"


namespace cppGameDev {
extern SDL_GameController* a;

/**
 * @brief Represents the RGB color values.
 */
struct RGB {
  Uint8 r; /**< The red component. */
  Uint8 g; /**< The green component. */
  Uint8 b; /**< The blue component. */
};

/**
 * @brief Represents the speed in the x and y directions.
 */
struct Speed {
  double x; /**< The speed in the x direction. */
  double y; /**< The speed in the y direction. */
};

/**
 * @brief Represents the coordinates in the x and y directions.
 */
struct Cord {
  int x; /**< The x coordinate. */
  int y; /**< The y coordinate. */
};

/**
 * @brief Represents the coordinates in the left, right, up, and down
 * directions.
 */
struct Cord4d {
  int l; /**< The left coordinate. */
  int r; /**< The right coordinate. */
  int u; /**< The up coordinate. */
  int d; /**< The down coordinate. */
};

// struct tile in "tilemap.hpp"

extern const Uint32 FULLSCREEN;    /**< The flag for fullscreen mode. */
extern const Uint32 SHOW_HITBOXES; /**< The flag for showing hitboxes. */

extern Uint32 kFlags; /**< The global flags variable. */

extern SDL_Window *screen;      /**< The game window. */
extern SDL_Renderer *renderer;  /**< The renderer for drawing graphics. */
extern SDL_Texture *display;    /**< The texture for displaying graphics. */
extern SDL_Texture *ui_display; /**< The texture for displaying UI graphics. */

extern Cord DisplaySize; /**< The size of the display. */
extern Cord ScreenSize;  /**< The size of the screen. */
extern int RenderScale;  /**< The scale factor for rendering. */

/**
 * @brief Retrieves the flags from the settings file and sets the appropriate
 * flags in the kFlags variable.
 */
void LoadSettings();

/**
 * @brief Initializes the game engine.
 *
 * @param title The title of the game window.
 * @param window_features The features of the game window.
 * @return True if the initialization is successful, false otherwise.
 */
bool Init(const char *title);

/**
 * @brief Deallocates resources and shuts down the engine.
 */
void Shutdown();
}  // namespace cppGameDev

#endif  // CPPGAMEDEV_CORE_ENGINE_HPP_