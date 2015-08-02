#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include "base.h"
#include "texture.h"
#include "sprite.h"
#include "button.h"

SDL_Window* g_pWindow = nullptr;
SDL_Renderer* g_pRenderer = nullptr;
//Globally used font
TTF_Font *g_pFont = nullptr;

//Mouse button sprites
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
TGfxTexture gButtonSpriteSheetTexture;

//Buttons objects
TButton * gButtons[TOTAL_BUTTONS];

bool LoadMedia()
{
	//Loading success flag
	bool bSuccess = true;

	//Load sprites
	if (!gButtonSpriteSheetTexture.loadFromFile("img/button.png"))
	{
		printf("Failed to load button sprite texture!\n");
		bSuccess = false;
	}
	else
	{
		//Set sprites
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
		{
			gSpriteClips[i].x = 0;
			gSpriteClips[i].y = i * 200;
			gSpriteClips[i].w = BUTTON_WIDTH;
			gSpriteClips[i].h = BUTTON_HEIGHT;
		}
		for (int i = 0; i < TOTAL_BUTTONS; i++){
			gButtons[i] = new TButton(&gButtonSpriteSheetTexture);
		}

		//Set buttons in corners
		gButtons[0]->setPosition(0, 0);
		gButtons[1]->setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
		gButtons[2]->setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
		gButtons[3]->setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
	}

	return bSuccess;
}
void Update()
{
	//Clear screen
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_pRenderer);

	//Render buttons
	for (int i = 0; i < TOTAL_BUTTONS; ++i)
	{
		gButtons[i]->render(gSpriteClips);
	}

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
				break;			
			}
			break;
		case SDL_QUIT:
			return true;
			break;
		}

		//Handle button events
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			gButtons[i]->handleEvent(&e);
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
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		
		//Create window
		g_pWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_pWindow == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			bSuccess = false;
		}
		else
		{
			//Create vsynced renderer for window
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (g_pRenderer == nullptr)
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

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					bSuccess = false;
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
		SDL_BlitSurface(pXOut, NULL, SDL_GetWindowSurface(g_pWindow), NULL);

		//Update the surface
		SDL_UpdateWindowSurface(g_pWindow);
	}

	//Wait two seconds
	SDL_Delay(1000);

	SDL_FreeSurface(pXOut);
	pXOut = nullptr;


	//----------Dellocation
	//Free loaded images

	//Free global font
	TTF_CloseFont(g_pFont);
	g_pFont = nullptr;

	
	//Destroy window
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	g_pRenderer = nullptr;
	g_pWindow = nullptr;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}