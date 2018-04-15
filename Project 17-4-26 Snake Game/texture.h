#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

#include <string>

class Texture
{
public:
	~Texture();

	void free();

	bool loadTextureFrom( std::string path );

	inline SDL_Texture* getTexture()
	{
		return texture;
	}

private:
	SDL_Texture* texture;

};

#endif

