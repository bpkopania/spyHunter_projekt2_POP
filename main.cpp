#include<stdio.h>
#include<string.h>

#include "SDL_handler.h"
#include "game.h"
#include "saver.h"

#include "config.h"

#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"

long long int scoreByRide(double time, int speed);

// main
int main(int argc, char **argv) {
	int t1, t2, quit, frames, rc;
	double delta, fpsTimer, fps;

	int bush_pos[BUSH_NUM] = { 0,12000,21000,29000 };

	_screen screen;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
									 &(screen.window), &(screen.renderer));
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(screen.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(screen.renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(screen.window, "Bartosz Kopania 193169");


	screen.screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
								  0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	screen.scrtex = SDL_CreateTexture(screen.renderer, SDL_PIXELFORMAT_ARGB8888,
							   SDL_TEXTUREACCESS_STREAMING,
							   SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	screen.charset = SDL_LoadBMP("./cs8x8.bmp");
	if(screen.charset == NULL) {
		on_exit(&screen);
		return 1;
		};
	SDL_SetColorKey(screen.charset, true, 0x000000);

	screen.car = SDL_LoadBMP("./car.bmp");
	if(screen.car == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		on_exit(&screen);
		return 1;
		};

	screen.bush = SDL_LoadBMP("./bush.bmp");
	if (screen.bush == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		on_exit(&screen);
		return 1;
	};

	screen.arrow = SDL_LoadBMP("./arrow.bmp");
	if (screen.arrow == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		on_exit(&screen);
		return 1;
	}

	char text[128];
	char textInfo[128];
	const int czarny = SDL_MapRGB(screen.screen->format, 0x00, 0x00, 0x00);
	const int zielony = SDL_MapRGB(screen.screen->format, 0x00, 0x99, 0x00);
	const int czerwony = SDL_MapRGB(screen.screen->format, 0xFF, 0x00, 0x00);
	const int niebieski = SDL_MapRGB(screen.screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	int timeForInfo = 0;
	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	game stats;

	while(!quit) {
		t2 = SDL_GetTicks();

		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		delta = (t2 - t1) * 0.001;
		t1 = t2;

		if (!stats.isPause)
		{
			stats.time += delta;

			fpsTimer += delta;
			if (fpsTimer > 0.5) {
				fps = frames * 2;
				frames = 0;
				fpsTimer -= 0.5;
			};
		}

		stats.newCar();

		SDL_FillRect(screen.screen, NULL, czarny);

		//road
		DrawRectangle(screen.screen, 0, 56, SCREEN_WIDTH / 2 - ROAD_WIDTH, SCREEN_HEIGHT - 52, zielony, zielony);
		DrawRectangle(screen.screen, SCREEN_WIDTH/2+ROAD_WIDTH, 56, SCREEN_WIDTH / 2 - ROAD_WIDTH, SCREEN_HEIGHT - 52, zielony, zielony);

		//bush
		DrawSurface(screen.screen, screen.bush, 60, (bush_pos[0] / BUSH_SPEED) + 46);
		DrawSurface(screen.screen, screen.bush, SCREEN_WIDTH - 50, (bush_pos[1] / BUSH_SPEED) + 46);
		DrawSurface(screen.screen, screen.bush, 130, (bush_pos[2] / BUSH_SPEED) + 46);
		DrawSurface(screen.screen, screen.bush, SCREEN_WIDTH - 120, (bush_pos[3] / BUSH_SPEED) + 46);

		// tekst informacyjny / info text
		DrawRectangle(screen.screen, 4, 4, SCREEN_WIDTH - 8, 52, czerwony, niebieski);
		sprintf_s(text, "Bartosz Kopania 193169 inf gr 4");
		DrawString(screen.screen, screen.screen->w / 2 - strlen(text) * 8 / 2, 10, text, screen.charset);
		// "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		sprintf_s(text, "Wynik: %.10i, speed: %.2ikm/h, czas trwania: %.1lf s  %.0lf klatek / s", stats.score, stats.speed, stats.time, fps);
		DrawString(screen.screen, screen.screen->w / 2 - strlen(text) * 8 / 2, 26, text, screen.charset);
		sprintf_s(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
		DrawString(screen.screen, screen.screen->w / 2 - strlen(text) * 8 / 2, 42, text, screen.charset);

		//display funcionalities
		DrawRectangle(screen.screen, SCREEN_WIDTH-260, SCREEN_HEIGHT - 36, 250, 26, czerwony, niebieski);
		sprintf_s(text, "abcdefgg im");
		DrawString(screen.screen, SCREEN_WIDTH-250, SCREEN_HEIGHT - 26, text, screen.charset);

		DrawSurface(screen.screen, screen.car, SCREEN_WIDTH / 2 + stats.position, SCREEN_HEIGHT - CAR_POS_FROM_BOTTOM - CAR_HEIGHT);

		
		if (timeForInfo > stats.time)
		{
			DrawString(screen.screen, 6, SCREEN_HEIGHT - 26, textInfo, screen.charset);
		}

		if (stats.isGameOver)
		{
			sprintf_s(text, "Game Over, Your Score is: %i, time: %.1lf", stats.score, stats.time);
			DrawString(screen.screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2, text, screen.charset);
		}

		if (!stats.isPause)
		{
			if (stats.time >= stats.peanulty) stats.score += scoreByRide(delta, stats.speed);
			for (int i = 0; i < BUSH_NUM; i++)
			{
				bush_pos[i] += stats.speed;
				bush_pos[i] %= (SCREEN_HEIGHT - 46) * BUSH_SPEED;
			}
		}
		else if (!stats.isGameOver)
		{
			sprintf_s(text, "Game is Paused");
			DrawString(screen.screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2, text, screen.charset);
		}

		SDL_UpdateTexture(screen.scrtex, NULL, screen.screen->pixels, screen.screen->pitch);
		SDL_RenderCopy(screen.renderer, screen.scrtex, NULL, NULL);
		SDL_RenderPresent(screen.renderer);

		//handling of events (if there were any)
		while(SDL_PollEvent(&(screen.event))) {
			switch(screen.event.type) {
				case SDL_KEYDOWN:
					if (screen.event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					else if (screen.event.key.keysym.sym == SDLK_n && !stats.isPause) stats.newGame();
					else if (screen.event.key.keysym.sym == SDLK_p && !stats.isGameOver) stats.pause();
					else if (screen.event.key.keysym.sym == SDLK_s && !stats.isGameOver)
					{ 
						if (save(stats))
						{
							sprintf_s(textInfo, "Game is Saved");
						}
						else
						{
							sprintf_s(textInfo, "Saving Failed!!!");
						}
						timeForInfo = stats.time + 5;
					}
					else if (screen.event.key.keysym.sym == SDLK_l)
					{
						if (name_getter(&stats, screen))
						{
							sprintf_s(textInfo, "Game is Loaded");
						}
						else
						{
							sprintf_s(textInfo, "Loading failed");
						}
						timeForInfo = stats.time + 5;
					}
					else if (screen.event.key.keysym.sym == SDLK_UP && !stats.isPause) stats.speeding();
					else if (screen.event.key.keysym.sym == SDLK_DOWN && !stats.isPause) stats.slowing();
					else if (screen.event.key.keysym.sym == SDLK_RIGHT && !stats.isPause) stats.movingToRight();
					else if (screen.event.key.keysym.sym == SDLK_LEFT && !stats.isPause) stats.movingToLeft();
					break;
				case SDL_KEYUP:
					break;
				case SDL_QUIT:
					quit = 1;
					break;
			};
		};
		frames++;
	};

	on_exit(&screen);
	return 0;
};

long long int scoreByRide(double time, int speed)
{
	return SCORE_BY_RIDE * time * speed;
}
