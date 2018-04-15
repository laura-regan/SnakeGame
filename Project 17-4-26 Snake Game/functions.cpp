#include "functions.h"

#include <SDL_image.h>

#include <random>

#include "constants.h"
#include "globals.h"



bool initialize()
{
	bool success = true;

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "Failed to start SDL! SDL Erorr: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		int initFlags = IMG_INIT_PNG;
		if ( !( IMG_Init( initFlags ) & initFlags ) )
		{
			printf( "Failed to start SDL_imgae! SDL_image Error: %s\n", IMG_GetError() );
			success = false;
		}
		else
		{
			gWindow = SDL_CreateWindow( "Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
			if ( gWindow == NULL )
			{
				printf( "Failed to create window! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
				if ( gRenderer == NULL )
				{
					printf( "Failed to create renderer! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
			}
		}
	}


	return success;
}

bool checkCollision( SDL_Rect colliderA, SDL_Rect colliderB )
{
	bool collisionFound = true;

	int leftA = colliderA.x;
	int topA = colliderA.y;
	int rightA = colliderA.x + colliderA.w;
	int bottomA = colliderA.y + colliderA.h;

	int leftB = colliderB.x;
	int topB = colliderB.y;
	int rightB = colliderB.x + colliderB.w;
	int bottomB = colliderB.y + colliderB.h;

	if ( rightA <= leftB )
	{
		collisionFound = false;
	}
	if ( leftA >= rightB  )
	{
		collisionFound = false;
	}
	if ( topA >= bottomB )
	{
		collisionFound = false;
	}
	if ( bottomA <= topB )
	{
		collisionFound = false;
	}
	

	return collisionFound;
}


bool loadMedia()
{
	bool success = true;
	Texture texture;
	
	if ( !sandBackground.loadTextureFrom( "Media/Sand_Background.png" ) )
	{
		success = false;
	}
	
	if ( !bodyTexture.loadTextureFrom( "Media/Snake_Body.png" ) )
	{
		success = false;
	}
	if ( !headTexture.loadTextureFrom( "Media/Snake_Head.png" ) )
	{
		success = false;
	}
	if ( !cornerTexture.loadTextureFrom( "Media/Snake_Corner.png" ) )
	{
		success = false;
	}
	if ( !tailTexture.loadTextureFrom( "Media/Snake_Tail.png" ) )
	{
		success = false;
	}
	if ( !fruitTexture.loadTextureFrom( "Media/Apple.png" ) )
	{
		success = false;
	}


	return success;
}


void endGame()
{
	
}


void close()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gRenderer = NULL;
	gWindow = NULL;

	sandBackground.free();

	headTexture.free();
	bodyTexture.free();
	cornerTexture.free();
	tailTexture.free();

	fruitTexture.free();

	IMG_Quit();
	SDL_Quit();
}

/*
template<typename T> void vectorPopFront( std::vector<T> &vector )
{
	int size = vector.size();
	for ( int i = 0; i < (size - 1); i++ )
	{
		vector[i] = vector[i + 1];
	}
	vector.pop_back;
}

*/


int getRandomNumber(int min, int max)
{
	std::random_device rd{};

	std::mt19937 engine{ rd() };


	//std::uniform_int_distribution<uint32_t> uint_dist;
	std::uniform_int_distribution<int> dist(min, max);
	//std::normal_distribution<double> normal_dist( mean, stddeviation );

	int randNum = dist( engine );

	return randNum;
}