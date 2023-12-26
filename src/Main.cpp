#include <iostream>
#include <SDL2/SDL.h>
#include "../include/Global.h"
#include "../include/Game.h"
#include "../include/Box.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool switche = false;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Surface* gScreenSurface = NULL;

SDL_Texture* gTexture = NULL;
SDL_Texture* gBackTexture = NULL;

TTF_Font* Font = NULL;

Box boxes[4][4] = {};

int main(int argc, char* args[]) {
    if (init()){
        SDL_Delay(1000);
        bool quit = false;
        SDL_Event e;
        int frameNumber;

        if (TTF_Init() == -1) {
            std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
            // Handle the error (e.g., return an error code or exit the program)
            return 1;
        }

        Font = TTF_OpenFont("../assets/fonts/modern_sans_serif_7.ttf", 100);
        if (Font == NULL) {
            std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
            // Handle the error (e.g., return an error code or exit the program)
            return 1;
        }


        for (int y = 0; y < 4; y++)
        {   
            for (int x = 0; x < 4; x++)
            {
                SDL_Rect rect = SDL_Rect();
                rect.h = 50;
                rect.w = 50;
                rect.x = (x * 60) + (SCREEN_WIDTH / 2 - 100);
                rect.y = (y * 60) + (SCREEN_HEIGHT / 2 - 100);

                boxes[y][x] = Box();
                boxes[y][x].init(gRenderer, &rect);
            }
        }

        add_new_2();

        while (!quit){
            frameNumber++;

            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT){
                    quit=true;
                }
                else if (e.type == SDL_KEYDOWN){
                    HandleKeys(e.key.keysym.sym);
                }
            }
            SDL_SetRenderDrawColor(gRenderer, 255, 230, 230, 255);
            SDL_RenderClear(gRenderer);

            SDL_Rect LRect = SDL_Rect();
            LRect.h = 260;
            LRect.w = 260;
            LRect.x = (SCREEN_WIDTH / 2 - 110);
            LRect.y = (SCREEN_HEIGHT / 2 - 110);

            SDL_RenderCopy(gRenderer, gBackTexture, NULL, &LRect);

            for (int y = 0; y < 4; y++)
            {   
                for (int x = 0; x < 4; x++)
                {
                    boxes[y][x].draw();
                }
            }

            SDL_Rect testRect;
            testRect.x = SCREEN_WIDTH / 2 - 100;
            testRect.y = 10;
            testRect.h = 100;
            testRect.w = 200;

            SDL_Color red = {255, 50, 50};

            DrawText(gRenderer, "2048", testRect, red);

            SDL_RenderPresent( gRenderer );
        }
        for (int y = 0; y < 4; y++)
        {   
            for (int x = 0; x < 4; x++)
            {
                boxes[y][x].exit();
            }
        }
        SDL_DestroyTexture(gBackTexture);
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);

        return 0;
    }else{
        return 1;
    }
}