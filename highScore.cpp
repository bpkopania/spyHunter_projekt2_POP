#include <stdio.h>
#include <string.h>

#include "highScore.h"
#include "SDL_handler.h"

void addScore(long long int scoreToSave, double timeToSave)
{
	FILE* scoresTimeFile;
	fopen_s(&scoresTimeFile, "scoresByTime.txt", "r");
	FILE* scoresScoreFile;
	fopen_s(&scoresScoreFile, "scoresByScore.txt", "r");

	_score time[MAX_SIZE_HIGHSCORE + 1] = { 0 };
	_score score[MAX_SIZE_HIGHSCORE + 1] = { 0 };

	if (scoresTimeFile != NULL && scoresScoreFile != NULL)
	{
		for (int i = 0; i < MAX_SIZE_HIGHSCORE; i++)
		{
			fscanf(scoresTimeFile, "%i %lf ", &(time[i].score), &(time[i].time));
			fscanf(scoresScoreFile, "%i %lf ", &(score[i].score), &(score[i].time));
		}
		fclose(scoresScoreFile);
		fclose(scoresTimeFile);
		time[5].score = scoreToSave;
		time[5].time = timeToSave;
		score[5].score = scoreToSave;
		score[5].time = timeToSave;
		orderByScore(score);
		orderByTime(time);
	}
	else
	{
		time[0].score = scoreToSave;
		time[0].time = timeToSave;
		score[0].score = scoreToSave;
		score[0].time = timeToSave;
	}

	fopen_s(&scoresTimeFile, "scoresByTime.txt", "w");
	fopen_s(&scoresScoreFile, "scoresByScore.txt", "w");
	if (scoresTimeFile != NULL && scoresScoreFile != NULL)
	{
		for (int i = 0; i < MAX_SIZE_HIGHSCORE; i++)
		{
			fprintf_s(scoresTimeFile, "%i %lf ", time[i].score, time[i].time);
			fprintf_s(scoresScoreFile, "%i %lf ", score[i].score, score[i].time);
		}
	}
}

//bool showScore(_screen screen, char mode)
//{
//	char text[128];
//	const int czarny = SDL_MapRGB(screen.screen->format, 0x00, 0x00, 0x00);
//	bool end = false;
//	_score ordered[MAX_SIZE_HIGHSCORE];
//	FILE* scoresFile;
//	if (mode == 's')
//	{
//		fopen_s(&scoresFile, "scoresByScore.txt", "r");
//	}
//	else if (mode == 't')
//	{
//		fopen_s(&scoresFile, "scoresByTime.txt", "r");
//	}
//	if (scoresFile != NULL)
//	{
//		while (!end)
//		{
//			SDL_FillRect(screen.screen, NULL, czarny);
//			for (int i = 0; i < MAX_SIZE_HIGHSCORE; i++)
//			{
//				sprintf_s(text, "%i. Score: %.10i Time: %.1lf", i + 1, ordered[i].score, ordered[i].time);
//				DrawString(screen.screen, screen.screen->w / 2 - strlen(text) * 8 / 2, i * 26 + 10, text, screen.charset);
//			}
//
//			SDL_UpdateTexture(screen.scrtex, NULL, screen.screen->pixels, screen.screen->pitch);
//			SDL_RenderCopy(screen.renderer, screen.scrtex, NULL, NULL);
//			SDL_RenderPresent(screen.renderer);
//
//			while (SDL_PollEvent(&(screen.event))) {
//				switch (screen.event.type) {
//				case SDL_KEYDOWN:
//					if (screen.event.key.keysym.sym == SDLK_ESCAPE) end = true;
//					break;
//				case SDL_KEYUP:
//					break;
//				case SDL_QUIT:
//					end = true;
//					break;
//				}
//			}
//			SDL_RenderClear(screen.renderer);
//		}
//		return true;
//	}
//	return false;
//}

void orderByTime(_score ordered[])
{
	for (int i = 0; i < MAX_SIZE_HIGHSCORE + 1; i++)
	{
		for (int j = 0; j < MAX_SIZE_HIGHSCORE - i; j++)
		{
			if (ordered[j].time > ordered[j + 1].time)
			{
				int tempScore = ordered[j].score;
				ordered[j].score = ordered[j + 1].score;
				ordered[j + 1].score = tempScore;

				double tempTime = ordered[j].time;
				ordered[j].time = ordered[j + 1].time;
				ordered[j + 1].time = tempTime;
			}
		}
	}
}

void orderByScore(_score ordered[])
{
	for (int i = 0; i < MAX_SIZE_HIGHSCORE + 1; i++)
	{
		for (int j = 0; j < MAX_SIZE_HIGHSCORE - i; j++)
		{
			if (ordered[j].score > ordered[j + 1].score)
			{
				int tempScore = ordered[j].score;
				ordered[j].score = ordered[j + 1].score;
				ordered[j + 1].score = tempScore;

				double tempTime = ordered[j].time;
				ordered[j].time = ordered[j + 1].time;
				ordered[j + 1].time = tempTime;
			}
		}
	}
}
