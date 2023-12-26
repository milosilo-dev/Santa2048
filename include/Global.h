#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <array>
#include <tuple>

#include "Renderer.h"
#include "Box.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* gWindow;

extern SDL_Surface* gScreenSurface;

extern SDL_Texture* gTexture;
extern SDL_Texture* gBackTexture;

extern TTF_Font* Font;

extern Box boxes[4][4];

#endif