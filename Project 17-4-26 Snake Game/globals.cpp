#include "globals.h"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Snake snake;

GameObjectManager gameObjectManager;

Texture sandBackground;

Texture bodyTexture;
Texture headTexture;
Texture cornerTexture;
Texture tailTexture;

Texture fruitTexture;

GameData gameData;