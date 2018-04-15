#include "snake.h"

#include <iterator>
#include <ctime>
#include <cstdlib>

#include "constants.h"
#include "globals.h"
#include "functions.h"

#include "texture.h" 





Snake::Snake()
{
	Segments.reserve( MAX_SNAKE_LENGTH );

	// Random direction
	direction = getRandomNumber(0, 3);

	// Random position
	int borderWidth = SCREEN_WIDTH * 0.2;
	int borderHeight = SCREEN_HEIGHT * 0.2;
	int x = getRandomNumber( borderWidth, SCREEN_WIDTH - borderWidth ); 
	int y = getRandomNumber( borderHeight , SCREEN_HEIGHT - borderHeight ); 

	SDL_Rect clip = { x, y, SNAKE_SEGMENT_WIDTH, SNAKE_SEGMENT_HEIGHT };

	Segment segment;

	segment.clip = clip;
	segment.direction = direction;
	segment.angle = 0;
	segment.textureType = BODY;

	Segments.push_back( segment );

	for ( int i = 1; i < INITIAL_SNAKE_LENGTH; i++ )
	{
		addNewSegment();
	}
}


void Snake::handleInput( SDL_Event e )
{
	if ( e.type == SDL_KEYDOWN )
	{
		switch ( e.key.keysym.sym )
		{
			case SDLK_UP:
				if ( direction != DOWN )
				{
					direction = UP;
				}
				break;
			case SDLK_DOWN:
				if ( direction != UP )
				{
					direction = DOWN;
				}
				break;
			case SDLK_RIGHT:
				if ( direction != LEFT )
				{
					direction = RIGHT;
				}
				break;
			case SDLK_LEFT:
				if ( direction != RIGHT )
				{
					direction = LEFT;
				}
				break;
		}
	}
}


void Snake::move()
{
	for ( int i = 0; i < Segments.size() - 1; i++ )
	{
		Segments[i] = Segments[i + 1];
	}
	Segments[Segments.size() - 1] = getNewSegment();
}


void Snake::render( SDL_Renderer* renderer )
{
	smoothCorners();

	for ( int i = 0; i < Segments.size(); i++ )
	{
		SDL_Rect clip = Segments[i].clip;
		float angle = Segments[i].angle;
		int textureType = Segments[i].textureType;
		SDL_Texture* texture = NULL;


		if ( textureType == BODY )
		{
			texture = bodyTexture.getTexture();
		}
		else if ( textureType == CORNER )
		{
			texture = cornerTexture.getTexture();
		}
		else if ( textureType == HEAD )
		{
			texture = headTexture.getTexture();
		}
		else if ( textureType == TAIL )
		{
			texture = tailTexture.getTexture();
		}

		SDL_RenderCopyEx( renderer, texture, NULL, &clip, angle, NULL, SDL_FLIP_NONE);
	}
}


Segment Snake::getNewSegment()
{
	int length = Segments.size();

	SDL_Rect currentClip = Segments[length - 1].clip;

	SDL_Rect clip = { currentClip.x, currentClip.y, SNAKE_SEGMENT_WIDTH, SNAKE_SEGMENT_HEIGHT };

	switch ( direction )
	{
		case UP:
			clip.y -= SNAKE_SEGMENT_WIDTH;
			if ( clip.y < 0 )
			{
				clip.y = SCREEN_HEIGHT - SNAKE_SEGMENT_HEIGHT;
			}
			break;
		case DOWN:
			clip.y += SNAKE_SEGMENT_WIDTH;
			if ( clip.y + SNAKE_SEGMENT_HEIGHT > SCREEN_HEIGHT )
			{
				clip.y = 0;
			}
			break;
		case RIGHT:
			clip.x += SNAKE_SEGMENT_WIDTH;
			if ( clip.x + SNAKE_SEGMENT_WIDTH > SCREEN_WIDTH )
			{
				clip.x = 0;
			}
			break;
		case LEFT:
			clip.x -= SNAKE_SEGMENT_WIDTH;
			if ( clip.x < 0 )
			{
				clip.x = SCREEN_WIDTH - SNAKE_SEGMENT_WIDTH;
			}
			break;
	}

	Segment newSegment;

	newSegment.clip = clip;
	newSegment.direction = direction;

	return newSegment;
}


void Snake::findCorners()
{
	int length = Segments.size();
	int currentDirection;
	int nextDirection;
	for ( int i = 1; i < length - 1; i++ )
	{
		currentDirection = Segments[i].direction;
		nextDirection = Segments[i + 1].direction;
		if ( currentDirection != nextDirection )
		{
			Segments[i].textureType = CORNER;
		}
		else
		{
			Segments[i].textureType = BODY;
		}
	}
}


void Snake::addNewSegment()
{
	Segment newSegment = getNewSegment();
	Segments.push_back( newSegment );
}


bool Snake::doesSnakeOverlap()
{
	bool overlapFound = false;

	unsigned length = Segments.size();

	SDL_Rect headSegment = Segments[length - 1].clip;

	for ( int i = 0; i < length - 3; i++ )
	{
		SDL_Rect bodySegment = Segments[i].clip;

		if ( checkCollision( headSegment, bodySegment ) )
		{
			overlapFound = true;
		}
	}

	return overlapFound;
}


void Snake::smoothCorners()
{

	findCorners();

	int length = Segments.size();

	// Tail
	int tailDirection = Segments[1].direction;

	Segments[0].textureType = TAIL;

	if ( tailDirection == RIGHT )
	{
		Segments[0].angle = 0.0;
	}
	else if ( tailDirection == DOWN )
	{
		Segments[0].angle = 90.0;
	}
	else if ( tailDirection == LEFT )
	{
		Segments[0].angle = 180.0;
	}
	else if ( tailDirection == UP )
	{
		Segments[0].angle = 270.0;
	}


	// Body
	for ( int i = 1; i < length - 1; i++ )
	{
		int nextDirection = Segments[i + 1].direction;
		int currentDirection = Segments[i].direction;

		if ( Segments[i].textureType == CORNER )
		{
			if ( ( currentDirection == RIGHT && nextDirection == UP ) || ( currentDirection == DOWN && nextDirection == LEFT ) )
			{
				Segments[i].angle = 0.0; 
			}
			else if ( ( currentDirection == LEFT && nextDirection == UP ) || ( currentDirection == DOWN && nextDirection == RIGHT ))
			{
				Segments[i].angle = 90.0;
			}
			else if ( ( currentDirection == LEFT && nextDirection == DOWN ) || ( currentDirection == UP && nextDirection == RIGHT ) )
			{
				Segments[i].angle = 180.0;
			}
			else if ( ( currentDirection == RIGHT && nextDirection == DOWN ) || ( currentDirection == UP && nextDirection == LEFT ) )
			{
				Segments[i].angle = 270.0;
			}
		}
		else if ( Segments[i].textureType == BODY )
		{
			if ( currentDirection == UP || currentDirection == DOWN )
			{
				Segments[i].angle = 90.0;
			}
			else if ( currentDirection == RIGHT || currentDirection == LEFT )
			{
				Segments[i].angle = 0.0;
			}
		}
	}

	// Head
	int headDirection = Segments[length - 1].direction;

	Segments[length - 1].textureType = HEAD;

	if ( headDirection == RIGHT )
	{
		Segments[length - 1].angle = 0.0;
	}
	else if ( headDirection == UP )
	{
		Segments[length - 1].angle = -90.0;
	}
	else if ( headDirection == LEFT )
	{
		Segments[length - 1].angle = 180.0;
	}
	else if ( headDirection == DOWN )
	{
		Segments[length - 1].angle = 90.0;
	}




}