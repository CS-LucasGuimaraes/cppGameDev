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

#include "core/imageHandle.hpp"

namespace cppGameDev {

std::string BASE_PATH = "../assets/images/";

SDL_Texture* load_image(const char* path) {
  SDL_Texture* img = IMG_LoadTexture(cppGameDev::renderer, path);
  SDL_SetTextureBlendMode(img, SDL_BLENDMODE_BLEND);
  return img;
}

const std::vector<SDL_Texture*> load_images(const char* path) {
  std::vector<SDL_Texture*> images;
  for (auto const& file :
       std::filesystem::directory_iterator((BASE_PATH + path).c_str())) {
    images.push_back(load_image(
        (BASE_PATH + std::string(path) + "/" + file.path().filename().string())
            .c_str()));
    std::clog << "    " << std::string(path) << "/"
              << file.path().filename().string() << " loaded.\n";
  }

  return images;
}

void RenderCentralizedText(std::string text, TTF_Font* font, int size,
                           SDL_Color color, SDL_Rect text_rect) {
  TTF_SetFontSize(font, size * kRenderScale);

  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);

  if (!surfaceMessage) {
    std::cerr << "[WARNING!] TEXT SURFACE INITIALIZATION FAILED!\n"
              << "     [SDL]: " << SDL_GetError() << '\n';
  }

  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

  if (!Message) {
    std::cerr << "[WARNING!] TEXT TEXTURE INITIALIZATION FAILED!\n"
              << "     [SDL]: " << SDL_GetError() << '\n';
  }

  text_rect.h *= kRenderScale;
  text_rect.w *= kRenderScale;
  text_rect.x *= kRenderScale;
  text_rect.y *= kRenderScale;

  int box_x = text_rect.w;
  int box_y = text_rect.h;

  TTF_SizeText(font, text.c_str(), &text_rect.w, &text_rect.h);

  text_rect.x += int((box_x - text_rect.w) / 2);
  text_rect.y += int((box_y - text_rect.h) / 2);


  SDL_Texture* prev = SDL_GetRenderTarget(renderer);

  SDL_SetRenderTarget(renderer, ui_display);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, Message, NULL, &text_rect);

  SDL_SetRenderTarget(renderer, prev);

  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
}

}  // namespace cppGameDev