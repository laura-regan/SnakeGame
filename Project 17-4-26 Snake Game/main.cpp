#include <SDL.h>

#include <stdio.h>
#include <ctime>
#include <cstdlib>

#include "globals.h"
#include "functions.h"

#include "snake.h"
#include "game_object_manager.h"
#include "fruit.h"

int main( int argc, char* args[] )
{
	if ( !initialize() )
	{
		printf( "SDL failed to initialize!\n\n" );
	}
	else
	{

		if ( !loadMedia() )
		{
			printf( "Failed to load media!\n\n" );
		}
		else
		{
			
			SDL_Event e;

			int frame = 0;

			bool quit = false;
			while ( !quit )
			{
				while ( SDL_PollEvent( &e ) != 0 )
				{
					if ( e.type == SDL_QUIT || snake.doesSnakeOverlap() )
					{
						quit = true;
					}
					else
					{
						snake.handleInput( e );
					}
				}

				if ( frame / Snake::VELOCITY == 1 )
				{
					snake.move();
				}

				if ( getRandomNumber(0, 150) == 1 )
				{
					if ( getRandomNumber(0, 100) == 1 )
					{
						gameObjectManager.spawn();
						gameObjectManager.spawn();
					}
					else
					{
						gameObjectManager.spawn();
					}
					
				}
				
				gameObjectManager.update();
				
				gameObjectManager.remove();

				

				

				//SDL_Delay( 10000 );
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );



				SDL_RenderCopy( gRenderer, sandBackground.getTexture(), NULL, NULL );

				snake.render( gRenderer );

				gameObjectManager.render();

				SDL_RenderPresent( gRenderer );

				frame++;
				if ( frame > Snake::VELOCITY )
				{
					frame = 0;
				}
			}
		}
	}

	close();

	return 0;
}