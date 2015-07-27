#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "base.h"
#include "texture.h"
#include "sprite.h"

SDL_Window* g_pWindow = nullptr;
SDL_Surface* g_pScreenSurface = nullptr;
SDL_Surface* g_pStretchedSurface = nullptr;

SDL_Renderer* g_pRenderer = nullptr;

TGfxSprite gSpriteClips[4];
TGfxTexture gSpriteSheetTexture;
Uint8 a = 255;

bool LoadMedia()
{
	//Loading success flag
	bool bSuccess = true;

	//Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile("img/dots.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
		bSuccess = false;
	}
	else
	{
		//UL
		SDL_Rect clip = { 0, 0, 100, 100 };
		gSpriteClips[0].loadFromTexture(&gSpriteSheetTexture, clip);

		//UR
		clip = { 100, 0, 100, 100 };
		gSpriteClips[1].loadFromTexture(&gSpriteSheetTexture, clip);
		gSpriteClips[1].setX(SCREEN_WIDTH - clip.w);
		
		//DL
		clip = { 0, 100, 100, 100 };
		gSpriteClips[2].loadFromTexture(&gSpriteSheetTexture, clip);
		gSpriteClips[2].setY(SCREEN_HEIGHT - clip.h);

		//DR
		clip = { 100, 100, 100, 100 };
		gSpriteClips[3].loadFromTexture(&gSpriteSheetTexture, clip);
		gSpriteClips[3].setX(SCREEN_WIDTH - clip.w);
		gSpriteClips[3].setY(SCREEN_HEIGHT - clip.h);

		gSpriteSheetTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	return bSuccess;
}
void Update()
{
	//Clear screen
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_pRenderer);

	gSpriteSheetTexture.setAlpha(a);

	//Render top left sprite
	gSpriteClips[0].render();
	//Render top right sprite
	gSpriteClips[1].render();
	//Render bottom left sprite
	gSpriteClips[2].render();
	//Render bottom right sprite
	gSpriteClips[3].render();

	//Update screen
	SDL_RenderPresent(g_pRenderer);
}
bool Inputs(SDL_Event e)
{
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_DOWN:
				if (a - 32 < 0) a = 0;
				else a -= 32;
				break;
			case SDLK_UP:
				if (a + 32 > 255) a = 255;
				else a += 32;
				break;			
			}
			break;
		case SDL_QUIT:
			return true;
			break;
		}
	}
	return false;
}




bool Init()
{
	//Initialization flag
	bool bSuccess = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		bSuccess = false;
	}
	else
	{
		//Create window
		g_pWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_pWindow == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			bSuccess = false;
		}
		else
		{
			//Create renderer for window
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED);
			if (g_pRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				bSuccess = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					bSuccess = false;
				}
				else
				{
					//Get window surface
					g_pScreenSurface = SDL_GetWindowSurface(g_pWindow);
				}
			}
		}
	}

	return bSuccess;
}
void Loop(bool(*inputs)(SDL_Event e), void(*update)())
{
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event ev = SDL_Event();
	
	//While application is running
	while (!quit)
	{
		if (inputs(ev)) quit = true;
		update();
	}
}
void Close()
{
	//-------Closing
	SDL_Surface* pXOut = SDL_LoadBMP("img/x.bmp");
	if (pXOut == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "x.bmp", SDL_GetError());
	}
	else{
		//Apply the image
		SDL_BlitSurface(pXOut, NULL, g_pScreenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(g_pWindow);
	}

	//Wait two seconds
	SDL_Delay(1000);

	SDL_FreeSurface(pXOut);
	pXOut = nullptr;


	//----------Dellocation

	gSpriteClips[0].free();
	gSpriteClips[1].free();
	gSpriteClips[2].free();
	gSpriteClips[3].free();
	gSpriteSheetTexture.free();

	//Deallocate surface
	SDL_FreeSurface(g_pScreenSurface);
	g_pScreenSurface = nullptr;

	//Destroy window
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	g_pRenderer = nullptr;
	g_pWindow = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(g_pRenderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, g_pScreenSurface->format, NULL);
		if (optimizedSurface == nullptr)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}