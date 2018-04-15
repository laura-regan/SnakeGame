#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SDL.h>

class GameObject
{
	static const int WIDTH = 35;
	static const int HEIGHT = WIDTH;

	GameObject();

	void place( SDL_Rect rect );

	void render( SDL_Renderer* &renderer );

	SDL_Rect getRect()
	{
		return clip;
	}

private:
	SDL_Rect clip;

	int posX;
	int posY;
};

#endif
