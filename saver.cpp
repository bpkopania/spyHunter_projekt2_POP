#include <stdio.h>
#include <time.h>
#include <string.h>

#include "game.h"

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
			fprintf_s(save, "speed: %i time: %lf score: %lli position: %i peanulty: %lf %i lives: %i new_cars: %i ammo: %i",
				stats.speed, stats.time, stats.score, stats.position, stats.peanulty, stats.peanulty_start, stats.lives, stats.newCars, stats.gun.ammo);
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

bool load(game *stats)
{
	FILE* save;
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
				//fscanf_s(names, "%s", nameOfFiles[i]);
				fscanf(names, "%s", nameOfFiles[i]);
			}
			fclose(names);

			fopen_s(&save, nameOfFiles[0], "r");
			if (save != NULL)
			{
				fscanf_s(save, "speed: %i time: %lf score: %lli position: %i peanulty: %lf %i lives: %i new_cars: %i ammo: %i",
					&(stats->speed), &(stats->time), &(stats->score), &(stats->position), &(stats->peanulty), &(stats->peanulty_start), &(stats->lives), &(stats->newCars), &(stats->gun.ammo));

				stats->isPause = true;
				fclose(save);
				return true;
			}
		}
	}	
	
	return false;
}
