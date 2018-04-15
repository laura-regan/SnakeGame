#ifndef FRUIT_H
#define FRUIT_H

#include <SDL.h>

class Fruit
{
public:
	static const int WIDTH = 35;
	static const int HEIGHT = WIDTH;

	static const int LIFE_TIME = 300;

	Fruit();

	void place(SDL_Rect rect);

	void render( SDL_Renderer* &renderer );

	void reduceLife();

	bool isAlive();

	SDL_Rect getClip()
	{
		return clip;
	}

private:
	SDL_Rect clip;

	int posX;
	int posY;

	int life;
};
#endif
