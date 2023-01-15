#pragma once

#include "config.h"

#define ROAD_WIDTH 150
#define ROAD_MARGIN 20
#define CAR_WIDTH 20
#define CAR_HEIGHT 62

#define STARTING_LIVES 2

#define GOD_MODE_TIME 30
#define NO_ENEMY_TIME 10

#define PEANULTY_TIME 10

#define NO_POWER_UP 10
#define POWER_PROB 10

#define AWARD 100000

#define MAX_SPEED 45
#define TURN_SPEED 4

#define BASIC_DISTANCE 150
#define MAX_DISTANCE 300
#define MAX_AMMO 15
#define MIN_AMMO 5

#define NEW_CAR_PROB 1000
#define CAR_TURN_PROB 1000
#define MAX_SPEED_ENEMY 60

#define ENEMY_DOWN 10000
#define ENEMY_CODE 1

struct _position {
	int x;
	int y;
};

class game
{
public:
	int speed;
	double wtime;
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
		_position position;
	} cars[MAXCARS];

	struct _powerUp {
		bool alive;
		_position position;
	} powerUp;
	
	game();

	void newGame();

	void speeding();

	void slowing();

	void movingToRight();

	void movingToLeft();

	void pause();

	void liveDown();

	void newCar();

	void otherCarsHandler();

	void shooting();

	void powerUpHandler();

private:
	void game_setter();

	void gameOver();

	void setNewCar(int index);

	void touching(int index);

	void moveToSide(char side);

	void newPowerUp();

	void setNewGun();
};

