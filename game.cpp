#include "game.h"

game::game()
{
	isPause = false;
	game_setter();
}

void game::newGame()
{
	game_setter();
}

void game::speeding()
{
	if (speed < MAX_SPEED)
		speed++;
}

void game::slowing()
{
	if (speed > 0)
		speed--;
}

void game::movingToRight()
{
	if (speed > 0)
	{
		if (position < ROAD_WIDTH - CAR_WIDTH)
			position += TURN_SPEED;
		else if (position < ROAD_WIDTH - CAR_WIDTH + ROAD_MARGIN && speed > 0)
		{
			position += TURN_SPEED;
			speed /= 2;
		}
		else
		{
			liveDown();
		}
	}
}

void game::movingToLeft()
{
	if (speed > 0)
	{
		if (position > -ROAD_WIDTH + CAR_WIDTH)
			position -= TURN_SPEED;
		else if (position > -ROAD_WIDTH + CAR_WIDTH - ROAD_MARGIN && speed > 0)
		{
			position -= TURN_SPEED;
			speed /= 2;
		}
		else
		{
			liveDown();
		}
	}
}

void game::pause()
{
	isPause = !isPause;
}

void game::game_setter()
{
	gun.ammo = -1;
	gun.distance = BASIC_DISTANCE;
	newCars = 0;
	isGameOver = false;
	speed = 0;
	time = 0;
	score = 0;
	position = 0;
	peanulty = 0;
	peanulty_start = 0;
	lives = STARTING_LIVES;
	isPause = false;
}

void game::liveDown()
{
	if (time > GOD_MODE_TIME)
	{
		lives--;
	}
	if (lives < 0)
	{
		gameOver();
	}
	else
	{
		speed = 0;
		position = 0;
		peanulty = time + PEANULTY_TIME;
	}
}

void game::gameOver()
{
	isPause = true;
	isGameOver = true;
}
