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