#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"

struct _screen
{
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* car;
	SDL_Surface* bush;
	SDL_Surface* arrow;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

void on_exit(_screen* screen);
