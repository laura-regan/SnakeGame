#include "texture.h"

#include <SDL_image.h>

#include <stdio.h>

#include "globals.h"


Texture::~Texture()
{
	free();
}

void Texture::free()
{
	if ( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
	}
}

bool Texture::loadTextureFrom( std::string path )
{
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if ( loadedSurface == NULL )
	{
		printf( "Failed to load surface from path %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if ( texture == NULL )
		{
			printf( "Failed to create texture from surface! SDL Error: %s\n", SDL_GetError() );
		}
	}

	SDL_FreeSurface( loadedSurface );
	loadedSurface = NULL;

	return texture != NULL;
}