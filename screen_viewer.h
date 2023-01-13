#pragma once

#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define SCORE_BY_RIDE 30
#define CAR_POS_FROM_BOTTOM 30

#define BUSH_SPEED 30
#define BUSH_NUM 4

class screen_viewer
{
public:
	int t1, t2, quit, frames, rc;
	double delta, fpsTimer, fps;

	int bush_pos[BUSH_NUM] = { 0,12000,21000,29000 };

	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* car;
	SDL_Surface* bush;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	set_new();
};

