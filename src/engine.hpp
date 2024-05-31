#ifndef engine_hpp
#define engine_hpp

#include <SDL2/SDL.h>
#include <SDL2/sdl_image.h>

#include <bits/stdc++.h>

using __SDL_Texture = DECLSPEC SDL_Texture * SDLCALL;
using __SDL_Renderer = DECLSPEC SDL_Renderer * SDLCALL;

extern SDL_Window *screen;
extern SDL_Renderer *display;

#endif