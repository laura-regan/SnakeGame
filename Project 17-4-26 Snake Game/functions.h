#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL.h>

#include <vector>

bool initialize();
bool checkCollision( SDL_Rect colliderA, SDL_Rect colliderB );
bool loadMedia();
void endGame();
void close();
int getRandomNumber( int min, int max );

template<typename T> 

void vectorPopFront(std::vector<T> &vector)
{
	int size = vector.size();
	for ( int i = 0; i < ( size - 1 ); i++ )
	{
		vector[i] = vector[i + 1];
	}
	vector.pop_back();
}

#endif

