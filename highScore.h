#pragma once

#include "SDL_handler.h"

#define MAX_SIZE_HIGHSCORE 10

struct _score {
	long long int score;
	double time;
};

void addScore(long long int scoreToSave, double timeToSave);

bool showScore(char mode, _screen screen);

void orderByTime(_score ordered[]);

void orderByScore(_score ordered[]);

char modePicker(_screen screen);
