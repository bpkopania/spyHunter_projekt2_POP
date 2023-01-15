#include <time.h>
#include <stdlib.h>

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
	wtime = 0;
	score = 0;
	position = 0;
	peanulty = 0;
	//peanulty_start = 0;
	lives = STARTING_LIVES;
	isPause = false;
	for (int i = 0; i < MAXCARS; i++)
	{
		cars[i].speed = -1;
	}
}

void game::liveDown()
{
	if (wtime > GOD_MODE_TIME)
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
		peanulty = wtime + PEANULTY_TIME;
	}
}

void game::gameOver()
{
	isPause = true;
	isGameOver = true;
}

void game::newCar()
{
	if (score > AWARD && newCars < 1)
	{
		lives++;
		newCars++;
	}
	else if (score > 2 * AWARD && newCars < 2)
	{
		lives++;
		newCars++;
	}
	else if (score > 3 * AWARD && newCars < 3)
	{
		lives++;
		newCars++;
	}
}

void game::otherCarsHandler()
{
	if (wtime > NO_ENEMY_TIME)
	{
		int probability;
		for (int i = 0; i < MAXCARS; i++)
		{
			if (cars[i].speed == -1)
			{
				probability = rand() % NEW_CAR_PROB;
				if (probability == 0)
					setNewCar(i);
			}

			cars[i].position.y -= cars[i].speed - speed;

			if (cars[i].position.y > (SCREEN_HEIGHT + CAR_HEIGHT + CAR_HEIGHT)*BUSH_SPEED  || cars[i].position.y < 0 - CAR_HEIGHT)
			{
				cars[i].speed = -1;
			}

		}
	}
}

void game::setNewCar(int index)
{
	//srand(time(NULL));
	cars[index].speed = rand() % (MAX_SPEED_ENEMY - 10) + 10;
	cars[index].position.x = rand() % ((ROAD_WIDTH - CAR_WIDTH)* 2) - ROAD_WIDTH + CAR_WIDTH;
	cars[index].attitiude = rand() % 2;
	if (cars[index].speed > speed)
	{
		cars[index].position.y = (SCREEN_HEIGHT + CAR_HEIGHT / 2) * BUSH_SPEED;
	}
	else
	{
		cars[index].position.y = 0;
	}
}

void game::shooting()
{
	for (int i = 0; i < MAXCARS; i++)
	{
		int range = 480 - CAR_POS_FROM_BOTTOM - CAR_HEIGHT / 2 - gun.distance;
		range *= BUSH_SPEED;
		if (cars[i].position.x > position - 2 * CAR_WIDTH
			&& cars[i].position.x < position + 2 * CAR_WIDTH
			&& cars[i].position.y > range
			&& cars[i].position.y/BUSH_SPEED < SCREEN_HEIGHT - CAR_POS_FROM_BOTTOM - CAR_HEIGHT)
		{
			if (cars[i].attitiude == 1)
			{
				score += AWARD;
			}
			else
			{
				peanulty = wtime + PEANULTY_TIME;
			}
			cars[i].speed = -1;
		}
	}
}
