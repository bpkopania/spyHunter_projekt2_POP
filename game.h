#pragma once

#define ROAD_WIDTH 120
#define ROAD_MARGIN 20
#define CAR_WIDTH 20
#define CAR_HEIGHT 62

#define STARTING_LIVES 3

#define MAX_SPEED 45
#define TURN_SPEED 4

class game
{
public:
	int speed;
	double time;
	long long int score;
	int position;
	int peanulty;
	int peanulty_start;
	int lives;
	bool isPause;
	
	game();

	void newGame();

	void speeding();

	void slowing();

	void movingToRight();

	void movingToLeft();

	void pause();
};

