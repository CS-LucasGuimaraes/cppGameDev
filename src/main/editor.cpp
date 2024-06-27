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

#include "main/editor.hpp"

namespace cppGameDev {

Editor::Editor() {
  this->tilemap = new Tilemap();
  this->tile_list = {{"grass", "background"}};
  this->tile_group = 0;
  this->tile_variant = 0;
  this->movement = {0, 0, 0, 0};

  this->scrollSpeed = 2;
  this->isRunning = true;
  this->scroll = {0, 0};
  this->mpos = {0, 0};
  this->clicking = false;
  this->right_clicking = false;
  this->ongrid = true;

  this->control = false;
  this->shift = false;
  this->alt = false;

  this->layer = 127;
}

Editor::~Editor() {
  delete this->tilemap;
  std::clog << "Editor class successfully destroyed!\n";
}

bool Editor::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        this->isRunning = false;
        return false;

      case SDL_KEYDOWN:
        if (assets::keybinds["LEFT"].count(event.key.keysym.sym)) {
          this->movement.l = 1;
        } else if (assets::keybinds["RIGHT"].count(event.key.keysym.sym)) {
          this->movement.r = 1;
        } else if (assets::keybinds["UP"].count(event.key.keysym.sym)) {
          this->movement.u = 1;
        } else if (assets::keybinds["DOWN"].count(event.key.keysym.sym)) {
          this->movement.d = 1;
        } else if (event.key.keysym.sym == SDLK_LCTRL) {
          this->control = true;
        } else if (event.key.keysym.sym == SDLK_LSHIFT) {
          this->shift = true;
        } else if (event.key.keysym.sym == SDLK_LALT) {
          this->alt = true;
        }

        break;

      case SDL_KEYUP:
        if (assets::keybinds["LEFT"].count(event.key.keysym.sym)) {
          this->movement.l = 0;
        } else if (assets::keybinds["RIGHT"].count(event.key.keysym.sym)) {
          this->movement.r = 0;
        } else if (assets::keybinds["UP"].count(event.key.keysym.sym)) {
          this->movement.u = 0;
        } else if (assets::keybinds["DOWN"].count(event.key.keysym.sym)) {
          this->movement.d = 0;
        } else if (event.key.keysym.sym == SDLK_LCTRL) {
          this->control = false;
        } else if (event.key.keysym.sym == SDLK_LSHIFT) {
          this->shift = false;
        } else if (event.key.keysym.sym == SDLK_LALT) {
          this->alt = false;
        }

        break;

      case SDL_MOUSEMOTION:
        SDL_GetMouseState(&this->mpos.x, &this->mpos.y);

        break;

      case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button) {
          case SDL_BUTTON_LEFT:
            this->clicking = true;
            break;

          case SDL_BUTTON_RIGHT:
            this->right_clicking = true;
            break;

          case SDL_BUTTON_MIDDLE:

            break;
        }
        break;

      case SDL_MOUSEBUTTONUP:
        switch (event.button.button) {
          case SDL_BUTTON_LEFT:
            this->clicking = false;
            break;

          case SDL_BUTTON_RIGHT:
            this->right_clicking = false;
            break;

          case SDL_BUTTON_MIDDLE:

            break;
        }
        break;

      case SDL_MOUSEWHEEL:
        if (this->alt) {
          if (event.wheel.y > 0) {
            this->layer++;
          } else if (event.wheel.y < 0) {
            this->layer--;
          }
        } else if (this->shift) {
          if (event.wheel.y > 0) {
            this->tile_variant =
                (this->tile_variant + 1) %
                assets::tiles[this->tile_list[this->tile_group].first].size();
          } else if (event.wheel.y < 0) {
            this->tile_variant =
                (this->tile_variant - 1) %
                assets::tiles[this->tile_list[this->tile_group].first].size();
          }
        } else {
          if (event.wheel.y > 0) {
            this->tile_group = (this->tile_group + 1) % this->tile_list.size();
          } else if (event.wheel.y < 0) {
            this->tile_group = (this->tile_group - 1) % this->tile_list.size();
          }
        }

        break;
    }
  }
  return true;
}

void Editor::update() {
  this->cameraControl();

  if (this->ongrid) {
    Cord tilepos = this->getTilePos();
    std::string tile_loc =
        std::to_string(tilepos.x) + ";" + std::to_string(tilepos.y);

    if (this->clicking) {
      this->tilemap->tilemap[this->layer][tile_loc] = {
          this->tile_list[this->tile_group].first, this->tile_variant, tilepos,
          this->tile_list[this->tile_group].second};
      this->tilemap->layers.insert(this->layer);
    }

    if (this->right_clicking) {
      if (this->tilemap->tilemap[this->layer].count(tile_loc) != 0) {
        this->tilemap->tilemap[this->layer].erase(tile_loc);
      }
    }
  }

  else {
  }
}

void Editor::render() {
  SDL_SetRenderTarget(renderer, display);
  SDL_RenderClear(renderer);

  this->tilemap->render(this->scroll);
  this->RenderTilePreview();
  this->RenderLayerPreview();

  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, display, NULL, NULL);
  SDL_RenderCopy(renderer, ui_display, NULL, NULL);

  SDL_RenderPresent(renderer);
}

void Editor::RenderTilePreview() {
  Cord tile_cord = this->getTilePos();
  SDL_Rect tile_rect = {tile_cord.x * this->tilemap->tile_size - this->scroll.x,
                        tile_cord.y * this->tilemap->tile_size - this->scroll.y,
                        this->tilemap->tile_size, this->tilemap->tile_size};

  SDL_Rect preview = {kDisplaySize.x - (int)(this->tilemap->tile_size * 1.5),
                      0 + (int)(this->tilemap->tile_size * 0.5),
                      this->tilemap->tile_size, this->tilemap->tile_size};

  SDL_Texture* tile_img = assets::tiles[this->tile_list[this->tile_group].first]
                                       [this->tile_variant];

  Uint8 prev;
  SDL_GetTextureAlphaMod(tile_img, &prev);
  SDL_SetTextureAlphaMod(tile_img, 192);

  SDL_RenderCopy(renderer, tile_img, NULL, &tile_rect);

  SDL_SetTextureAlphaMod(tile_img, prev);

  SDL_RenderCopy(renderer, tile_img, NULL, &preview);
  SDL_RenderCopy(renderer, assets::ui["border"][7], NULL, &preview);
}

void Editor::RenderLayerPreview() {
  SDL_Rect preview = {0 + (int)(this->tilemap->tile_size * 0.5),
                      0 + (int)(this->tilemap->tile_size * 0.5),
                      this->tilemap->tile_size, this->tilemap->tile_size};

  SDL_RenderCopy(renderer, assets::ui["transparent_center"][7], NULL, &preview);

  RenderCentralizedText(std::to_string(int(this->layer)),
                        assets::fonts["monospaced"].first,
                        assets::fonts["monospaced"].second, {100, 100, 100},
                        {0 + (int)(this->tilemap->tile_size * 0.5),
                         0 + (int)(this->tilemap->tile_size * 0.5),
                         this->tilemap->tile_size, this->tilemap->tile_size});
}

void Editor::cameraControl() {
  this->scroll.x += (this->movement.r - this->movement.l) * this->scrollSpeed;
  this->scroll.y += (this->movement.d - this->movement.u) * this->scrollSpeed;
}

Cord Editor::getTilePos() {
  return {(int)std::floor((((double)this->mpos.x / (double)kRenderScale) +
                           (double)this->scroll.x) /
                          (double)this->tilemap->tile_size),
          (int)std::floor((((double)this->mpos.y / (double)kRenderScale) +
                           (double)this->scroll.y) /
                          (double)this->tilemap->tile_size)};
}
}  // namespace cppGameDev