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

#ifndef CPPGAMEDEV_CORE_ENGINE_HPP_
#define CPPGAMEDEV_CORE_ENGINE_HPP_

#include <bits/stdc++.h>

#include "SDL2/SDL.h"
#include "SDL2/sdl_image.h"
#include "nlohmann/json.hpp"

namespace cppGameDev {

using __SDL_Texture = DECLSPEC SDL_Texture *SDLCALL;
using __SDL_Renderer = DECLSPEC SDL_Renderer *SDLCALL;

struct RGB {
    Uint8 r;
    Uint8 g;
    Uint8 b;
};

struct Speed {
    float x;
    float y;
};

struct Cord {
    int x;
    int y;
};

// struct tile in "tilemap.hpp"

extern SDL_Window *screen;
extern SDL_Renderer *renderer;
extern SDL_Texture *display;

extern const Cord kDisplaySize;
extern const Cord kScreenSize;
extern const int kRenderScale;

/**
 * Initializes the game window, renderer, and sets up basic properties.
 *
 * \param title (const char*): The title of the game window.
 * \param window_features (SDL_Rect): The X and Y pos and width and height of
 * the game window in pixels. \param fullscreen (bool): Whether to run the game
 * in fullscreen mode. \returns (bool): This function returns true on success,
 * or false on failure (e.g., loading errors).
 */
bool Init(const char *title, SDL_Rect window_features, bool fullscreen);

/**
 * Deallocates resources and shuts down the engine.
 *
 * \returns (void): This function does not return a value.
 */
void Shutdown();
}  // namespace cppGameDev

#endif // CPPGAMEDEV_CORE_ENGINE_HPP_