
#include "main.h"

void Close();

LTexture gSpriteSheetTexture;	
LTexture gBackgroundTexture;	
LTexture gCookieTexture;
LTexture gCookieDownTexture;

LTexture gimg1;
LTexture gimg2;
LTexture gimg3;
LTexture gimg4;
LTexture gimg5;
LTexture gimg6;
LTexture gimg7;

LTexture gcmap;

bool loadMedia(){
	bool success = true;

	if( !gSpriteSheetTexture.loadFromFile( "../data/images/anim/foo.png" ) ){
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		gSpriteClips[ 0 ].x = 0;
		gSpriteClips[ 0 ].y = 0;
		gSpriteClips[ 0 ].w = 64;
		gSpriteClips[ 0 ].h = 205;

		gSpriteClips[ 1 ].x = 64;
		gSpriteClips[ 1 ].y = 0;
		gSpriteClips[ 1 ].w = 64;
		gSpriteClips[ 1 ].h = 205;

		gSpriteClips[ 2 ].x = 128;
		gSpriteClips[ 2 ].y = 0;
		gSpriteClips[ 2 ].w = 64;
		gSpriteClips[ 2 ].h = 205;

		gSpriteClips[ 3 ].x = 196;
		gSpriteClips[ 3 ].y = 0;
		gSpriteClips[ 3 ].w = 64;
		gSpriteClips[ 3 ].h = 205;
	}
	
	if(!gCookieTexture.loadFromFile    ("../data/images/cookie1.png")){printf("Failed!\n");success = false;}
	if(!gCookieDownTexture.loadFromFile("../data/images/cookie2.png")){printf("Failed!\n");success = false;}
	
	if(!gimg1.loadFromFile("../data/images/center.png"))    {printf("Failed!\n");success = false;}
	if(!gimg2.loadFromFile("../data/images/sidebar1.png"))  {printf("Failed!\n");success = false;}
	if(!gimg3.loadFromFile("../data/images/sidebar2.png"))  {printf("Failed!\n");success = false;}
	if(!gimg4.loadFromFile("../data/images/sidebar3.png"))  {printf("Failed!\n");success = false;}
	if(!gimg5.loadFromFile("../data/images/sidebar4.png"))  {printf("Failed!\n");success = false;}
	if(!gimg6.loadFromFile("../data/images/sidebar5.png"))  {printf("Failed!\n");success = false;}
	
	if(!gimg7.loadFromFile("../data/images/background.png")){printf("Failed!\n");success = false;}
	
	if(!gcmap.loadFromFile("c:/z/_MI/data/font/cmap.png"))  {printf("Failed!\n");success = false;}

	// if( !gBackgroundTexture.loadFromFile( "../images/anim/foo.png" ) ){
	// 	printf( "Failed to load walking animation texture!\n" );
	// 	success = false;
	// }else{
	// 	gBGSpriteClips[0].x = 0;
	// 	gBGSpriteClips[0].y = 0;
	// 	gBGSpriteClips[0].w = 128;
	// 	gBGSpriteClips[0].h = 50;
	// }
	
	return success;
}

void rectangleBoundsMouseOver(int x,int y,int w,int h,Uint8 r,Uint8 g,Uint8 b,Uint8 a,bool hover){
	
	int mx, my;
	bool drawfilltrue = false;

	SDL_GetMouseState(&mx,&my);
	
	if(mx>=x && my>=y && mx<=w+x && my<=h+y){
		drawfilltrue = true;
	}else{
		drawfilltrue = false;
	}

	if(drawfilltrue && hover){
		drawFillRect(x,y,w,h,r,g,b,a);
	}
	else{
		drawOutlineRect(x,y,w,h,r,g,b,a);
	}
}

static SDL_Surface *screen;
static SDL_Surface *cmap;
enum ck_t {magenta, lime};

int load_image(char filename[], SDL_Surface **surface, enum ck_t colour_key) {
	
	SDL_Surface *temp;
	
	temp = SDL_LoadBMP(filename);
	
	if (temp == NULL)
	{
		printf("Unable to load %s.\n", filename);
		return 1;
	}

	Uint32 colourkey;

	if (colour_key == magenta)
	{
		colourkey = SDL_MapRGB(temp->format, 255, 0, 255);
	
	} else if (colour_key == lime)
	{
		colourkey = SDL_MapRGB(temp->format, 0, 255, 0);
	}

	//SDL_SetColorKey(temp, SDL_SRCCOLORKEY, colourkey);
	//(*surface) = SDL_DisplayFormat(temp);
	
	if ((*surface) == NULL)
	{
		printf("Unable to convert bitmap.\n");
		return 1;
	}
	
	SDL_FreeSurface(temp);

	return 0;
}

int draw_char(char c, int x, int y)
{
	char *map[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
						"abcdefghijklmnopqrstuvwxyz",
						"!@#$%^&*()_+{}|:\"<>?,.;'-=",
						"0123456789"};
	
	for(int i = 0; i < 4; i++)
	{
		for(unsigned int j = 0; j < strlen(map[i]); j++)
		{
			if(c == map[i][j])
			{
				gMapSpriteClips[ 0 ].x = 20*j;
				gMapSpriteClips[ 0 ].y = 20*i;
				gMapSpriteClips[ 0 ].w = 20;
				gMapSpriteClips[ 0 ].h = 20;
				gcmap.render(x,y,1,1,gMapSpriteClips);	
				return(0);
			}
			gMapSpriteClips[ 0 ].x += 20;
		}
		gMapSpriteClips[ 0 ].y += 20;
		gMapSpriteClips[ 0 ].x += 0;
	}
	return 0;
}

void draw_string(char s[], int x, int y)
{
	for(unsigned int i = 0; i < strlen(s); i++)
	{
		draw_char(s[i],x,y);
		x += 20;
	}
}

int main(int argc, char* args[])
{
	init_Window(200,200,SCREEN_WIDTH_HALF,SCREEN_HEIGHT_HALF,3,1);
	//init_window();
	loadMedia();
	
 	int x = 0;
 	int y = 0;

	Region r =  { 20,    100, 250, 250};
	Region r2 = {  0,      0,  20,  20};
	Region r3 = {190,    200, 320,  60};
	Region r4 = {190, 200+65, 320,  60};
	
	bool keydown = false;
	bool incrementclicks = false;
	int counter = 0;
	int clicks = 0;
	static int val1 = 0,val2 = 0;

	//GAMELOOP
	while(running){
		while(POLLEVENT){
			if(QUIT){ exit(0); }
			if(UPPRESS){}
			if(DOWNPRESS){if(ESCAPE){exit(0);}}
			if(MOUSEBUTTONUP)
			{
				keydown = false;
			}
			if(MOUSEBUTTONDOWN)
			{
				if(LEFTMOUSEBUTTON)
				{
					
					if(gamestate == menu)
					{
						if(MX(r3)){ gamestate = game;  }
						if(MX(r4)){ running   = false; }
					}
					
					if(gamestate == game)
					{
						if(MX(r))
						{
							keydown = true;
							clicks++;
						}
						if(MX(r2)){ incrementclicks = true;  }

					}
				}
			}
			if(MOUSEMOTION){

			}
		}		
		SDL_SetRenderDrawColor(renderer,BLACK);
		SDL_RenderClear(renderer);

		if(gamestate == menu)
		{

			drawFillRect(r3.x,r3.y, r3.w,r3.h, 0,50,0,255);//start
			drawFillRect(r4.x,r4.y, r4.w,r4.h, 0,50,0,255);//exit
			//drawFontSolid(gFont,text,solidTexture,solidRect,renderer,1,0,5,r3.x+160,r3.y,"StartGame",255,255,255,255,"../res/fonts/arial.ttf",62);
			//drawFontSolid(gFont,text,solidTexture,solidRect,renderer,1,0,5,r3.x+160,r3.y+60,"Exit",255,255,255,255,"../res/fonts/arial.ttf",62);
			
			char hi1[] = "StartGame";               draw_string(hi1,r3.x,r3.y);
			char hi2[] = "Exit";                    draw_string(hi2,r3.x,r3.y+60);
		}

		if(gamestate == game)
		{

			gimg7.render(0,0,6,6); //background image
		
			/*
			  if(incrementclicks)//INCREMENTS CLICKS BY
			  {
			  if(counter >= 200 && clicks < 100) // clicks <= 200  and  counter <= 200
			  {
			  clicks += 2;
			  counter = 0;
			  }
			  else if(counter >= 100 && clicks >= 100 && clicks <= 300 ) // clicks >= 100 <= 300  and  counter > 100
			  {
			  clicks += 10;
			  counter = 0;
			  }
			  else
			  {
			  counter = 0;
			  }
			  counter++;
			  }
			  /**/
		
			/**/
			//CONVERSION FROM INT TO CONST CHAR*
			int filenameindex = clicks;
			std::stringstream strs;
			strs<<(clicks);
			std::string str = strs.str();
			const char* cstr = str.c_str();

			char hi3[] = ":Click";
			draw_string(hi3,100,30);
			
			char clicksbuffer [32];
			
			//_itoa_s: integer to string numerical base to represent the value
			// value between: 2 - 35,
			//10 decimal, 16 hex, 8 octal, 2 binary
			
			_itoa_s(clicks,clicksbuffer,10);
			draw_string(clicksbuffer,20,30);
			
			//DRAW TEXT "CLICKS : 0"
			//drawFontSolid(gFont,text,solidTexture,solidRect,renderer,0,0,5,100,0,":Click",255,255,255,255,"../res/fonts/1arial.ttf",62);
			//drawFontSolid(gFont,text,solidTexture,solidRect,renderer,2,0,5,100,0,cstr,255,255,255,255,"../res/fonts/arial.ttf",62);
			/**/
		
			/**/
			//CENTER RECT
			gimg1.render(280,100,6,6);//center
			/**/

			/*
			//SIDEBAR OUTLINES
			drawOutlineRect(renderer, 600, 50+50,100,50, MAGENTA);
			drawOutlineRect(renderer, 600,100+50,100,50, MAGENTA);
			drawOutlineRect(renderer, 600,150+50,100,50, MAGENTA);
			drawOutlineRect(renderer, 600,200+50,100,50, MAGENTA);
			drawOutlineRect(renderer, 600,250+50,100,50, MAGENTA);
			/**/
		
			/**/
			//SIDEBAR FILLER
			if(clicks >= 5)
			{
				//drawFillRect(renderer, 600,100,100,50, 0,255,0,255);
				gimg2.render(590,100,4,4);
				if(clicks >= 10)
				{
					//drawFillRect(renderer, 600,150,100,50, 12,50,255,255);
					gimg3.render(590,150,4,4);
					if(clicks >= 20)
					{
						//drawFillRect(renderer, 600,200,100,50, 120,20,220,255);
						gimg4.render(590,200,4,4);
						if(clicks >= 25)
						{
							//drawFillRect(renderer, 600,250,100,50, 40,240,140,255);
							gimg5.render(590,250,4,4);
							if(clicks >= 30)
							{
								//drawFillRect(renderer, 600,300,100,50, 255,255,0,255);
								gimg6.render(590,300,4,4);
							}
						}
					}
				}
			}
		
			/**/
			//COOKIE RECT && OUTLINE
			//drawFillRect(renderer,    r.x,r.y, r.w,r.h, 0,120,0,255);
			//drawOutlineRect(renderer, r.x,r.y, r.w,r.h, MAGENTA);

			if(keydown)
			{
				gCookieTexture.render(20,80,8,8);
			}
			else
			{
				gCookieDownTexture.render(20,80,8,8);
			}
			/**/
			
		}
		
		/*
		//ANIMATE IMAGE
		//BACKGROUND IMAGE
		SDL_Rect* bgClip = &gBGSpriteClips[ 0 ];
		gBackgroundTexture.render( 0, 0, 1,1,bgClip );

		//ANIMATION SPRITE
		SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
		gSpriteSheetTexture.render(X + (SCREEN_WIDTH - currentClip->w ) / 4,
										  (Y + SCREEN_HEIGHT - currentClip->h ) / 4,
										  1,1,
										  currentClip);
		++frame;
		if(frame / 4 >= WALKING_ANIMATION_FRAMES){ frame = 0; }
		/**/

		Sleep(1000/33);
		SDL_RenderPresent(renderer);
	}
	
	Close();
	return(0);
}

void Close()
{

	//gModulatedTexture.free();
	gBackgroundTexture.free();
	gSpriteSheetTexture.free();
	gCookieTexture.free();
	gCookieDownTexture.free();
	gimg1.free();
	gimg2.free();
	gimg3.free();
	gimg4.free();
	gimg5.free();
	gimg6.free();
	gimg7.free();
	gcmap.free();

	IMG_Quit();
	
	destroy_Window();
}
