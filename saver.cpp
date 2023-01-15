#include <stdio.h>
#include <time.h>
#include <string.h>

#include "game.h"
#include "SDL_handler.h"
#include "saver.h"

#include "config.h"

void move_up(int* pos)
{
	if (*pos > 0)
		(*pos)--;
}

void move_down(int* pos, int n)
{
	if (*pos < n - 1)
		(*pos)++;
}

bool save(game stats)
{
	FILE* save;
	FILE* number;
	FILE* names;

	int numberOfFiles;

	char nameOfFile[51];

	time_t _time = time(NULL);
	tm __time = *localtime(&_time);
	strftime(nameOfFile, sizeof(nameOfFile), "%Y-%m-%d_%H_%M_%S.txt", &__time);

	//reading the number of files
	fopen_s(&number, "num.txt", "r");
	if (number != NULL)
	{
		fscanf_s(number, "%i", &numberOfFiles);
		fclose(number);
	}
	else
	{
		numberOfFiles = 0;
	}

	fopen_s(&number, "num.txt", "w");
	fopen_s(&names, "names.txt", "a");

	if (number != NULL && names != NULL)
	{
		
		fopen_s(&save, nameOfFile, "w");
		if (save != NULL)
		{
			//increasing the files Number
			numberOfFiles++;
			fprintf_s(number, "%i", numberOfFiles);

			fprintf_s(names, "%s\n", nameOfFile);

			//saving info about game
			fprintf_s(save, "speed: %i time: %lf score: %lli position: %i peanulty: %lf lives: %i new_cars: %i gun: %i %i",
				stats.speed, stats.wtime, stats.score, stats.position, stats.peanulty, stats.lives, stats.newCars, stats.gun.ammo, stats.gun.distance);
			
			fprintf_s(save, "otherCars:\n");
			for (int i = 0; i < MAXCARS; i++)
			{
				fprintf_s(save, "speed: %i, attitiude: %i, pos: %i %i", stats.cars[i].speed, stats.cars[i].attitiude, stats.cars[i].position.x, stats.cars[i].position.y);
			}

			fclose(save);
			fclose(number);
			fclose(names);
			return true;
		}
		fclose(number);
		fclose(names);
	}
	return false;
	
	
}

bool load(game* stats, char* name)
{
	FILE* save;

	fopen_s(&save, name, "r");
	if (save != NULL)
	{
		fscanf_s(save, "speed: %i time: %lf score: %lli position: %i peanulty: %lf lives: %i new_cars: %i gun: %i %i",
			&(stats->speed), &(stats->wtime), &(stats->score), &(stats->position), &(stats->peanulty), &(stats->lives), &(stats->newCars), &(stats->gun.ammo), &(stats->gun.distance));

		stats->isPause = true;
		fclose(save);
		return true;
	}
	return false;
}

bool name_getter(game *stats, _screen screen)
{
	FILE* number;
	FILE* names;

	int numberOfFiles;

	char str[26];

	fopen_s(&number, "num.txt", "r");
	if (number != NULL)
	{
		fscanf_s(number, "%i", &numberOfFiles);
		fclose(number);
		char** nameOfFiles;
		nameOfFiles = new char* [numberOfFiles];

		fopen_s(&names, "names.txt", "r");
		if (names != NULL)
		{
			for (int i = 0; i < numberOfFiles; i++)
			{
				nameOfFiles[i] = new char[51];
				fscanf(names, "%s", nameOfFiles[i]);
			}
			fclose(names);

			int pos = 0;
			bool choosen = false;
			const int czarny = SDL_MapRGB(screen.screen->format, 0x00, 0x00, 0x00);
			//const int zielony = SDL_MapRGB(screen.screen->format, 0x00, 0x99, 0x00);
			char text[128];

			while (!choosen)
			{
				SDL_FillRect(screen.screen, NULL, czarny);
				//DrawRectangle(screen.screen, SCREEN_WIDTH / 2 + ROAD_WIDTH, 56, SCREEN_WIDTH / 2 - ROAD_WIDTH, SCREEN_HEIGHT - 52, zielony, zielony);

				for (int i = 0; i < numberOfFiles; i++)
				{
					sprintf_s(text, "%s",nameOfFiles[i]);
					DrawString(screen.screen, screen.screen->w / 2 - strlen(text) * 8 / 2, i*26+10, text, screen.charset);
				}

				DrawSurface(screen.screen, screen.arrow, SCREEN_WIDTH/2-120, pos*26+10);

				SDL_UpdateTexture(screen.scrtex, NULL, screen.screen->pixels, screen.screen->pitch);
				SDL_RenderCopy(screen.renderer, screen.scrtex, NULL, NULL);
				SDL_RenderPresent(screen.renderer);

				while (SDL_PollEvent(&(screen.event))) {
					switch (screen.event.type) {
					case SDL_KEYDOWN:
						if (screen.event.key.keysym.sym == SDLK_ESCAPE) choosen = true;
						else if (screen.event.key.keysym.sym == SDLK_RETURN) choosen = true;
						else if (screen.event.key.keysym.sym == SDLK_UP) move_up(&pos);
						else if (screen.event.key.keysym.sym == SDLK_DOWN) move_down(&pos, numberOfFiles);
						break;
					case SDL_KEYUP:
						break;
					case SDL_QUIT:
						choosen = true;
						break;
					}
				}
				SDL_RenderClear(screen.renderer);
			}

			if (load(stats, nameOfFiles[pos]))
				return true;
		}
	}	
	
	return false;
}
