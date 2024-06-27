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

#include "core/engine.hpp"

namespace cppGameDev {

const Uint32 FULLSCREEN = (1 << 0);
const Uint32 SHOW_HITBOXES = (1 << 1);

Uint32 kFlags = 0;

SDL_Window *screen = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *display = nullptr;
SDL_Texture *ui_display = nullptr;

const Cord kDisplaySize = {640, 360};
const Cord kScreenSize = {1280, 720};
const int kRenderScale = kScreenSize.x / kDisplaySize.x;

void getFlags() {
  YAML::Node config = YAML::LoadFile("../data/settings.yaml");

  if (config["fullscreen"].as<bool>()) {
    kFlags |= FULLSCREEN;
  }

  if (config["show_hitboxes"].as<bool>()) {
    kFlags |= SHOW_HITBOXES;
  }
}

bool Init(const char *title, SDL_Rect window_features) {
  Uint32 SDLflags = 0;

  getFlags();

  if (kFlags & FULLSCREEN) {
    SDLflags |= SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0) {
    std::clog << "SDL2 initialized!...\n";

    if (IMG_Init(IMG_INIT_PNG)) {
      std::clog << "SDL2_image initialized!...\n";
    } else {
      std::cerr << "[WARNING!] SDL2_IMAGE INITIALIZATION FAILED!\n";
    }

    if (TTF_Init()) {
      std::clog << "SDL2_ttf initialized!...\n";
    } else {
      std::cerr << "[WARNING!] SDL2_TTF INITIALIZATION FAILED!\n";
    }

    screen =
        SDL_CreateWindow("Cpp Game Dev", window_features.x, window_features.y,
                         window_features.w, window_features.h, SDLflags);
    if (screen) {
      std::clog << "Window created sucessfully!\n";
    } else {
      std::cerr << "[WARNING!] WINDOW INITIALIZATION FAILED!\n"
                << "     [SDL]: " << SDL_GetError() << '\n';
    }

    renderer = SDL_CreateRenderer(screen, -1, 0);
    if (renderer) {
      std::clog << "Redereer created sucessfully!\n";

      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    } else {
      std::cerr << "[WARNING!] RENDERER INITIALIZATION FAILED!\n"
                << "     [SDL]: " << SDL_GetError() << '\n';
    }

    display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, kDisplaySize.x,
                                kDisplaySize.y);
    if (display) {
      std::clog << "Display (render target) created sucessfully!\n";
      SDL_SetTextureBlendMode(ui_display, SDL_BLENDMODE_BLEND);

    } else {
      std::cerr << "[WARNING!] DISPLAY (RENDER TARGET) INITIALIZATION FAILED!\n"
                << "     [SDL]: " << SDL_GetError() << '\n';
    }

    ui_display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, kScreenSize.x,
                                kScreenSize.y);
    if (ui_display) {
      std::clog << "UI Display (render target) created sucessfully!\n";
      SDL_SetTextureBlendMode(ui_display, SDL_BLENDMODE_BLEND);

    } else {
      std::cerr << "[WARNING!] UI DISPLAY (RENDER TARGET) INITIALIZATION FAILED!\n"
                << "     [SDL]: " << SDL_GetError() << '\n';
    }

    return true;
  } else {
    std::cerr << "[WARNING!] SDL2 INITIALIZATION FAILED!\n";
    return false;
  }
}

void Shutdown() {
  SDL_DestroyWindow(screen);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(display);
  
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  std::clog << "Engine shutdown sucessfully!\n";
}
}  // namespace cppGameDev