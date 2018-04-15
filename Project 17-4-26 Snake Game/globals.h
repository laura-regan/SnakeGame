#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>

#include <vector>

#include "texture.h"
#include "snake.h"
#include "game_object_manager.h"
#include "game_data.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern Snake snake;

extern GameObjectManager gameObjectManager;

extern Texture sandBackground;

extern Texture bodyTexture;
extern Texture headTexture;
extern Texture cornerTexture;
extern Texture tailTexture;

extern Texture fruitTexture;

extern GameData gameData;

#endif