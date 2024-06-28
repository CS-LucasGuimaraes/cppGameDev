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

#include "main/game.hpp"

namespace cppGameDev {

Game::Game() {
  this->tilemap = new Tilemap();
  this->player = new Player({21, 21, 128, 128}, {64 - 7, 64 - 11, 14, 22}, "",
                            this->tilemap);
  this->movement = {0, 0, 0, 0};
  this->offset = {0, 0};
}

Game::~Game() {
  delete this->player;
  delete this->tilemap;
  std::clog << "Game class successfully destroyed!\n";
}

bool Game::handleEvents() {
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
        }

        break;

      // case SDL_CONTROLLERAXISMOTION:
      //   std::cout << "AXIS " << (int)event.caxis.axis << " VALUE "
      //             << event.caxis.value << '\n';
      //   break;
      // case SDL_CONTROLLERBUTTONDOWN:
      //   std::cout << "BUTTON " << (int)event.cbutton.button << " DOWN\n";
      //   break;
      // case SDL_CONTROLLERBUTTONUP:
      //   std::cout << "BUTTON " << (int)event.cbutton.button << " UP\n";
      //   break;
      

      // default:
      //   std::cout << "event type: " << event.type << '\n'; 
      //   break;
    }
  }
  return true;
}

void Game::update() {
  this->CameraControl();
  this->player->update(this->movement);

  this->movement.r = (SDL_GameControllerGetAxis(a, SDL_CONTROLLER_AXIS_LEFTX)/3276.7f);
  this->movement.d = (SDL_GameControllerGetAxis(a, SDL_CONTROLLER_AXIS_LEFTY)/3276.7f);

}

void Game::render() {
  SDL_SetRenderTarget(renderer, display);
  SDL_RenderClear(renderer);

  this->tilemap->render(this->offset);
  this->player->render(this->offset);

  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, display, NULL, NULL);

  SDL_RenderPresent(renderer);
}

void Game::CameraControl() {
  this->offset.x += (int)((this->player->getEntityRect().x +
                           this->player->getEntityRect().w / 2) -
                          DisplaySize.x / 2 - this->offset.x) /
                    64;
  this->offset.y += (int)((this->player->getEntityRect().y +
                           this->player->getEntityRect().h / 2) -
                          DisplaySize.y / 2 - this->offset.y) /
                    36;
}
}  // namespace cppGameDev