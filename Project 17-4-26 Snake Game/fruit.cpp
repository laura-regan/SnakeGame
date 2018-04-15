#include "fruit.h"

#include <ctime>
#include <cstdlib>

#include "globals.h"

Fruit::Fruit()
{
	posX = 0;
	posY = 0;

	clip = { posX, posY, WIDTH, HEIGHT };

	life = LIFE_TIME;
}


void Fruit::place( SDL_Rect rect )
{
	posX = rect.x;
	posY = rect.y;
	clip = rect;
}

void Fruit::render( SDL_Renderer* &renderer )
{
	SDL_RenderCopy( renderer, fruitTexture.getTexture(), NULL, &clip );
}


void Fruit::reduceLife()
{
	life--;
}


bool Fruit::isAlive()
{
	return life > 0;
}