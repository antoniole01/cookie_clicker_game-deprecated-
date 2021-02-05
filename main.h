#ifndef MAIN_H
#define MAIN_H

#include "pch.h"

#undef main

SDL_Window*		window = NULL;
SDL_Renderer*	renderer = NULL;
SDL_Texture*	solidTexture;
SDL_Texture*	text;
SDL_Rect			solidRect;
TTF_Font*		gFont = NULL;

SDL_Event e;

const int SCREEN_X				= 0;
const int SCREEN_Y				= 0;
const int SCREEN_WIDTH			= 1440;
const int SCREEN_HEIGHT			= 900;
const int SCREEN_WIDTH_HALF	= SCREEN_WIDTH / 2;
const int SCREEN_HEIGHT_HALF	= SCREEN_HEIGHT / 2;

bool running = true;

//WALKING ANIMATION
const int WALKING_ANIMATION_FRAMES = 4;

SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
SDL_Rect gBGSpriteClips    [ 1 ];
SDL_Rect gCookieSpriteClips[ 1 ];
SDL_Rect gMapSpriteClips[ 1 ];

int frame = 0;
int X,Y,XX,YY,XXX,YYY;

enum{menu,playerselect,game,credits};
int gamestate = menu;

#endif // MAIN_H
