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
	strftime(nameOfFile, sizeof(nameOfFile), "%Y %m %d %H %M %S.txt", &__time);

	//readind the number of files
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
			//if (fscanf_s(number, "%i", &numberOfFiles) == EOF)
				//numberOfFiles = 0;
			//else
				//fscanf_s(number, "%i", &numberOfFiles);
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

	char nameOfFile[51];

	fopen_s(&number, "num.txt", "r");
	if (number != NULL)
	{
		fscanf_s(number, "%i", &numberOfFiles);
		fclose(number);
	}
	else
	{
		return false;
	}

	fopen_s(&save, "save.txt", "r");
	if (save != NULL)
	{
		fscanf_s(save, "speed: %i time: %lf score: %lli position: %i peanulty: %lf %i lives: %i new_cars: %i ammo: %i",
			&(stats->speed), &(stats->time), &(stats->score), &(stats->position), &(stats->peanulty), &(stats->peanulty_start), &(stats->lives), &(stats->newCars), &(stats->gun.ammo));

		stats->isPause = true;
		fclose(save);
		return true;
	}
	return false;
}
