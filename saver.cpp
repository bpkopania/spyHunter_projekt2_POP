#include <stdio.h>
#include "game.h"

void save(game stats)
{
	FILE* file;
	char nameOfFile[51];
	
	fopen_s(&file, "save.txt", "w");
	if (file != NULL)
	{
		fprintf_s(file, "speed: %i time: %lf score: %lli position: %i peanulty: %i %i lives: %i",
			stats.speed, stats.time, stats.score, stats.position, stats.peanulty, stats.peanulty_start, stats.lives);
		fclose(file);
	}
}

void load(game *stats)
{
	FILE* file;
	char nameOfFile[51];

	fopen_s(&file, "save.txt", "r");
	if (file != NULL)
	{
		fscanf_s(file, "speed: %i time: %lf score: %lli position: %i peanulty: %i %i lives: %i",
			&(stats->speed), &(stats->time), &(stats->score), &(stats->position), &(stats->peanulty), &(stats->peanulty_start), &(stats->lives));

		stats->isPause = true;
		fclose(file);
	}
}
