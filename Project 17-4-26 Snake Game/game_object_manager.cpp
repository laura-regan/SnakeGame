#include "game_object_manager.h"

#include <ctime>
#include <cstdlib>

#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "fruit.h"
#include "game_data.h"

void GameObjectManager::spawn()
{
	std::srand( std::time( 0 ) );

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = Fruit::WIDTH;
	rect.h = Fruit::HEIGHT;


	bool positionAvailable = false;

	while ( !positionAvailable )
	{
		rect.x = getRandomNumber( 0, SCREEN_WIDTH - Fruit::WIDTH ); //std::rand() % ( SCREEN_WIDTH - Fruit::WIDTH );
		rect.y = getRandomNumber( 0, SCREEN_HEIGHT - Fruit::HEIGHT ); //std::rand() % ( SCREEN_HEIGHT - Fruit::HEIGHT );

		positionAvailable = true;
		for ( int i = 0; i < snake.getLength(); i++ )
		{
			if ( checkCollision( rect, snake.Segments[i].clip ) )
			{
				positionAvailable = false;
			}
		}

		for ( int i = 0; i < Fruits.size(); i++ )
		{
			if ( checkCollision( rect, Fruits[i].getClip() ) )
			{
				positionAvailable = false;
			}
		}

	}

	Fruit newFruit;
	newFruit.place( rect );
	Fruits.push_back( newFruit );
}


void GameObjectManager::update()
{
	int number = Fruits.size();
	for ( int i = 0; i < number; i++ )
	{
		Fruits[i].reduceLife();
	}
}


void GameObjectManager::remove()
{

	while ( Fruits.size() >= 1 && !Fruits[0].isAlive() )
	{
		vectorPopFront( Fruits );
	}

	for ( int i = 0; i < Fruits.size(); i++ )
	{
		if ( checkCollision( Fruits[i].getClip(), snake.Segments[snake.getLength() - 1].clip ) )
		{
			for ( int j = i; j < Fruits.size() - 1; j++ )
			{
				Fruits[i] = Fruits[i + 1];
			}
			Fruits.pop_back();
			snake.addNewSegment();
			gameData.ApplesEaten++;
			gameData.CurrentLength++;
		}
	}
}


void GameObjectManager::render()
{
	for ( int i = 0; i < Fruits.size(); i++ )
	{
		Fruits[i].render( gRenderer );
	}

}