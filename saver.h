#pragma once

#include "game.h"

void move_up(int* pos);

void move_down(int* pos, int n);

bool save(game stats);

bool load(game* stats, char* name);

bool name_getter(game* stats, _screen screen);
