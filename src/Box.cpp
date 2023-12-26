#include "../include/Box.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include "../include/Global.h"

using namespace std;

Box::Box() {
    this->texture = NULL;
    this->data = 0;
}

bool Box::init(SDL_Renderer* Renderer, SDL_Rect* rect){
    bool returnbool = true;
    if (Renderer == NULL){
        std::cout << "Entity Renderer Is Null. \n";
    } 

    this->rect = *rect;
    this->renderer = Renderer;

    this->data = 0;
    this->Black = {0,0,0};

    SDL_Surface* surface = SDL_LoadBMP("../assets/images/Box.bmp");
    this->texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_FreeSurface(surface);
    surface = NULL;
    return returnbool;
}

void Box::draw() {
    // Render box texture
    SDL_RenderCopy(this->renderer, this->texture, NULL, &this->rect);

    if (data != 0){
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        // Render text
        stringstream strs;
        strs << this->data;
        string temp_str = strs.str();
        const char* char_type = temp_str.c_str();

        SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Font, char_type, Black);

        if (surfaceMessage == nullptr) {
            std::cerr << "Error rendering text: " << TTF_GetError() << std::endl;
            return;
        }

        // Convert text surface to texture
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        if (Message == nullptr) {
            std::cerr << "Error creating text texture: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(surfaceMessage);
            return;
        }

        // Calculate a new rectangle for the text (e.g., below the box)
        SDL_Rect textRect = this->rect;
        textRect.y += 5;
        textRect.x += 12;
        textRect.h += 40;

        textRect.h = textRect.h/2;
        textRect.w = textRect.w/2;

        // Render text texture
        SDL_RenderCopy(renderer, Message, NULL, &textRect);

        // Cleanup resources
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);
    }
}

bool Box::checkData()
{
    return data > 0;
}

void Box::setData(int value)
{
    data = value;
}

int Box::getData()
{
    return data;
}

void Box::exit()
{
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;
}