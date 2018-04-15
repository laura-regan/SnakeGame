#include "game_object.h"

#include <ctime>
#include <cstdlib>

#include "globals.h"

GameObject::GameObject()
{
	posX = 0;
	posY = 0;

	clip = { posX, posY, WIDTH, HEIGHT };
}


void GameObject::place( SDL_Rect rect )
{
	posX = rect.x;
	posY = rect.y;
	clip = rect;
}

void GameObject::render( SDL_Renderer* &renderer )
{
	SDL_RenderCopy( renderer, fruitTexture.getTexture(), NULL, &clip );
}

