#include "game.h"

game::game()
{
	speed = 0;
	time = 0;
	score = 0;
	position = 0;
	peanulty = 0;
	peanulty_start = 0;
	lives = STARTING_LIVES;
	isPause = false;
}

void game::newGame()
{
	speed = 0;
	time = 0;
	score = 0;
	position = 0;
	peanulty = 0;
	peanulty_start = 0;
	lives = STARTING_LIVES;
	isPause = false;
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
			//TODO
			//GAME OVER
			//position = 0;
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
			//TODO
			//GAME OVER
			//position = 0;
		}
	}
}

void game::pause()
{
	isPause = !isPause;
}
