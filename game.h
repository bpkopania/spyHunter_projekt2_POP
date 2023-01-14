#pragma once

#include "config.h"

#define ROAD_WIDTH 150
#define ROAD_MARGIN 20
#define CAR_WIDTH 20
#define CAR_HEIGHT 62

#define STARTING_LIVES 2
#define GOD_MODE_TIME 30

#define PEANULTY_TIME 10

#define AWARD 100000

#define MAX_SPEED 45
#define TURN_SPEED 4

#define BASIC_DISTANCE 100

class game
{
public:
	int speed;
	double time;
	long long int score;
	int position;
	double peanulty;
	//int peanulty_start;
	int lives;
	bool isPause;
	bool isGameOver;
	int newCars;
	struct _gun {
		int ammo;
		int distance;
	} gun;

	struct _cars {
		int speed;
		int attitiude;
		struct _position {
			int x;
			int y;
		} position;
	} cars[MAXCARS];
	
	game();

	void newGame();

	void speeding();

	void slowing();

	void movingToRight();

	void movingToLeft();

	void pause();

	void liveDown();

	void newCar();

	void shooting();

private:
	void game_setter();

	void gameOver();
};

