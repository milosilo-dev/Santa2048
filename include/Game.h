#ifndef __SEA_H__
#define __SEA_H__
#include "../src/Game.cpp"
bool init();

bool loadMedia();

void DrawText(SDL_Renderer* renderer, const char* msg, SDL_Rect rect, SDL_Color color);

void add_new_2();

void HandleKeys(SDL_Keycode key);

const char* get_current_state();

bool compress();

bool merge();

void reverse();

void transpose();

bool up_move();
bool down_move();
bool right_move();
bool left_move();
#endif