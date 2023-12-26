#include "../include/Global.h"
#include "../include/Renderer.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <vector>

using namespace std;

bool loadMedia()
{
	SDL_Surface *surface = SDL_LoadBMP("../assets/images/Box.bmp");
	gTexture = SDL_CreateTextureFromSurface(gRenderer, surface);

	SDL_FreeSurface(surface);
	surface = NULL;

	surface = SDL_LoadBMP("../assets/images/BoxBack.bmp");
	gBackTexture = SDL_CreateTextureFromSurface(gRenderer, surface);

	SDL_FreeSurface(surface);
	surface = NULL;

	return 0;
}

bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		gWindow = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Get window surface
			// gScreenSurface = SDL_GetWindowSurface( gWindow );
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				loadMedia();
			}
		}
	}

	return success;
}

void DrawText(SDL_Renderer *renderer, const char *msg, SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Surface *surfaceMessage = TTF_RenderText_Shaded(Font, msg, color, {255, 230, 230});

	if (surfaceMessage == nullptr)
	{
		std::cerr << "Error rendering text: " << TTF_GetError() << std::endl;
		return;
	}

	// Convert text surface to texture
	SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	if (Message == nullptr)
	{
		std::cerr << "Error creating text texture: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(surfaceMessage);
		return;
	}

	// Calculate a new rectangle for the text (e.g., below the box)
	SDL_Rect textRect = rect;
	textRect.y += 5;
	textRect.x += 6;
	textRect.w -= 4;

	// Render text texture
	SDL_RenderCopy(renderer, Message, NULL, &textRect);

	// Cleanup resources
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void add_new_2()
{
	srand(time(0));
	while (true)
	{
		int randX = (random() % 4);
		int randY = (random() % 4);

		if (!boxes[randX][randY].checkData())
		{
			boxes[randX][randY].setData(2);
			break;
		}
	}
}

const char *get_current_state()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (boxes[y][x].getData() == 2048)
			{
				return "WON";
			}
			else if (boxes[y][x].getData() == 0)
			{
				return "GAME NOT OVER";
			}
		}
	}
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if ((boxes[y][x].getData() == boxes[y + 1][x].getData()) || (boxes[y][x].getData() == boxes[y][x + 1].getData()))
			{
				return "GAME NOT OVER";
			}
		}
		if (boxes[y][3].getData() == boxes[y + 1][3].getData())
		{
			return "GAME NOT OVER";
		}
	}
	for (int x = 0; x < 3; x++)
	{
		if (boxes[3][x].getData() == boxes[3][x + 1].getData())
		{
			return "GAME NOT OVER";
		}
	}
	return "LOST";
}

bool compress()
{
	bool changed = false;
	int boxes_new[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

	for (int y = 0; y < 4; y++)
	{
		int pos = 0;

		for (int x = 0; x < 4; x++)
		{
			if (boxes[y][x].getData() != 0)
			{
				boxes_new[y][pos] = boxes[y][x].getData();

				if (y != pos)
				{
					changed = true;
				}
				pos++;
			}
		}
	}
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			boxes[y][x].setData(boxes_new[y][x]);
		}
	}
	return changed;
}

bool merge() // i belive this works fine
{
	bool changed = false;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (boxes[y][x].checkData() == boxes[y][x + 1].checkData() && boxes[y][x].checkData() != 0)
			{
				boxes[y][x].setData(boxes[y][x].getData() * 2);
				boxes[y][x + 1].setData(0);

				changed = true;
			}
		}
	}

	return changed;
}

void reverse()
{
	std::vector<std::vector<int>> newMat;

	for (int i = 0; i < 4; ++i)
	{
		newMat.push_back(std::vector<int>());

		for (int j = 0; j < 4; ++j)
		{
			newMat[i].push_back(boxes[i][3 - j].getData());
		}
	}

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			boxes[y][x].setData(newMat[y][x]);
		}
	}
}

void transpose()
{
	std::vector<std::vector<int>> newMat;

	for (int i = 0; i < 4; ++i)
	{
		newMat.push_back(std::vector<int>());

		for (int j = 0; j < 4; ++j)
		{
			newMat[i].push_back(boxes[i][j].getData());
		}
	}

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			boxes[y][x].setData(newMat[y][x]);
		}
	}
}

bool left_move()
{
	bool changed = false;
	if (compress())
	{
		changed = true;
	}
	if (merge())
	{
		changed = true;
	}
	compress();
	return changed;
}

bool right_move()
{
	reverse();
	bool changed = left_move();

	reverse();
	return changed;
}

bool up_move()
{
	transpose();
	bool changed = left_move();
	transpose();

	return changed;
}

bool down_move()
{
	transpose();
	bool changed = right_move();
	transpose();

	return changed;
}

void HandleKeys(SDL_Keycode key)
{
	if (key == SDLK_UP)
	{
		if (up_move())
		{
			add_new_2();
		};
	}
	else if (key == SDLK_DOWN)
	{
		if (down_move())
		{
			add_new_2();
		};
	}
	else if (key == SDLK_LEFT)
	{
		if (left_move())
		{
			add_new_2();
		};
	}
	else if (key == SDLK_RIGHT)
	{
		if (right_move())
		{
			add_new_2();
		};
	}
}