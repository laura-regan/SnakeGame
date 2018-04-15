#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "snake.h"

struct GameData 
{
	int ApplesEaten = 0;
	int CurrentLength = Snake::INITIAL_SNAKE_LENGTH;
};

#endif
