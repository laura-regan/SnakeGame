#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>

#include <list>
#include <vector>

#include "texture.h"

const enum MOVEMENT_DIRECTIONS
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

const enum TEXTURES
{
	BODY,
	HEAD,
	CORNER,
	TAIL,
	TOTAL_TEXTURES
};


struct Segment {
	SDL_Rect clip;
	int direction;
	float angle = 0.0;
	unsigned textureType = BODY;
};

class Snake
{
public:
	// Segments
	static const int INITIAL_SNAKE_LENGTH = 17;
	static const int MAX_SNAKE_LENGTH = 160;

	// Segment dimensions in pixels
	static const int SNAKE_SEGMENT_WIDTH = 35;
	static const int SNAKE_SEGMENT_HEIGHT = 35;

	// Frames per movement
	static const int VELOCITY = 5;

	Snake();

	void handleInput( SDL_Event e );

	void addNewSegment();

	void move();

	void render( SDL_Renderer* renderer );

	bool doesSnakeOverlap();

	int getLength()
	{
		return Segments.size();
	}

	std::vector<Segment> Segments;
private:
	
	void smoothCorners();

	void findCorners();

	Segment getNewSegment();

	// Movement direction
	unsigned direction;
};

#endif 
