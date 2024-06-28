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
  SDL_GameController* a;

const Uint32 FULLSCREEN = (1 << 0);
const Uint32 SHOW_HITBOXES = (1 << 1);

Uint32 kFlags = 0;

SDL_Window *screen = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *display = nullptr;
SDL_Texture *ui_display = nullptr;

Cord ScreenSize;
Cord DisplaySize;
int RenderScale;

void LoadSettings() {
  YAML::Node settings = YAML::LoadFile("../data/settings.yaml");

  std::pair<int, int> ss = settings["screen_size"].as<std::pair<int, int>>();
  std::pair<int, int> ds = settings["display_size"].as<std::pair<int, int>>();

  ScreenSize = {ss.first, ss.second};
  DisplaySize = {ds.first, ds.second};
  RenderScale = ScreenSize.x / DisplaySize.x;

  if (settings["fullscreen"].as<bool>()) {
    kFlags |= FULLSCREEN;
  }

  if (settings["show_hitboxes"].as<bool>()) {
    kFlags |= SHOW_HITBOXES;
  }
}

bool Init(const char *title) {
  Uint32 SDLflags = 0;

  LoadSettings();

  if (kFlags & FULLSCREEN) {
    SDLflags |= SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0) {
    std::clog << "SDL2 initialized!...\n";

    if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG) {
      std::clog << "SDL2_image initialized!...\n";
    } else {
      std::cerr << "[WARNING!] SDL2_IMAGE INITIALIZATION FAILED!\n"
                << "     [SDL] " << IMG_GetError() << '\n';
    }

    if (TTF_Init() == 0) {
      std::clog << "SDL2_ttf initialized!...\n";
    } else {
      std::cerr << "[WARNING!] SDL2_TTF INITIALIZATION FAILED!\n"
                << "     [SDL] " << TTF_GetError() << '\n';
    }

    screen = SDL_CreateWindow("Cpp Game Dev", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, ScreenSize.x,
                              ScreenSize.y, SDLflags);
    if (screen) {
      std::clog << "Window created sucessfully!\n";
    } else {
      std::cerr << "[WARNING!] WINDOW INITIALIZATION FAILED!\n"
                << "     [SDL] " << SDL_GetError() << '\n';
    }

    renderer = SDL_CreateRenderer(screen, -1, 0);
    if (renderer) {
      std::clog << "Redereer created sucessfully!\n";

      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    } else {
      std::cerr << "[WARNING!] RENDERER INITIALIZATION FAILED!\n"
                << "     [SDL] " << SDL_GetError() << '\n';
    }

    display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, DisplaySize.x,
                                DisplaySize.y);
    if (display) {
      std::clog << "Display (render target) created sucessfully!\n";
      SDL_SetTextureBlendMode(ui_display, SDL_BLENDMODE_BLEND);

    } else {
      std::cerr << "[WARNING!] DISPLAY (RENDER TARGET) INITIALIZATION FAILED!\n"
                << "     [SDL] " << SDL_GetError() << '\n';
    }

    ui_display =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_TARGET, ScreenSize.x, ScreenSize.y);
    if (ui_display) {
      std::clog << "UI Display (render target) created sucessfully!\n";
      SDL_SetTextureBlendMode(ui_display, SDL_BLENDMODE_BLEND);

    } else {
      std::cerr
          << "[WARNING!] UI DISPLAY (RENDER TARGET) INITIALIZATION FAILED!\n"
          << "     [SDL] " << SDL_GetError() << '\n';
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