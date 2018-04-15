#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <vector>

#include "fruit.h"

class GameObjectManager
{
public:

	void spawn();

	void update();

	void remove();

	

	void render();

private:



	std::vector<Fruit> Fruits;

};

#endif

