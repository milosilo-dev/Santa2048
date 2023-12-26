#ifndef __BOX_H__
#define __BOX_H__
#include <SDL2/SDL.h>

class Box{
    public:
        Box();
        bool init(SDL_Renderer* Renderer, SDL_Rect* rect);
        void draw();
        bool checkData();
        void setData(int value);
        int getData();
        void exit();
    private:
        SDL_Texture* texture;
        SDL_Rect rect;
        SDL_Renderer* renderer;
        SDL_Color Black;
        int data;
};

#endif