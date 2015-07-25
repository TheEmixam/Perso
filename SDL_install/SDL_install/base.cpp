#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "base.h"

SDL_Window* g_pWindow = nullptr;
SDL_Surface* g_pScreenSurface = nullptr;
SDL_Surface* g_pStretchedSurface = nullptr;

SDL_Texture* g_pTexture = nullptr;
SDL_Renderer* g_pRenderer = nullptr;


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
bool LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	//g_pTexture = loadTexture("img/texture.png");
	//if (g_pTexture == nullptr)
	//{
	//	printf("Failed to load texture!\n");
	//	success = false;
	//}

	return success;
}

void Loop(void (*update)(), void (*close)())
{
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		update();
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}

	//Free resources and close SDL
	close();
}
void Update()
{
	//SDL_UpdateWindowSurface(g_pWindow);

	//Apply the image stretched
	//SDL_Rect stretchRect;
	//stretchRect.x = 0;
	//stretchRect.y = 0;
	//stretchRect.w = SCREEN_WIDTH;
	//stretchRect.h = SCREEN_HEIGHT;
	//SDL_BlitScaled(g_pStretchedSurface, NULL, g_pScreenSurface, &stretchRect);
	//SDL_BlitSurface(g_pStretchedSurface, NULL, g_pScreenSurface, NULL);

	//Clear screen
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_pRenderer);

	//Render texture to screen
	//SDL_RenderCopy(g_pRenderer, g_pTexture, NULL, NULL);

	//Render red filled quad
	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(g_pRenderer, &fillRect);

	//Render green outlined quad
	SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	SDL_SetRenderDrawColor(g_pRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(g_pRenderer, &outlineRect);

	//Draw blue horizontal line
	SDL_SetRenderDrawColor(g_pRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(g_pRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	//Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	for (int i = 0; i < SCREEN_HEIGHT; i += 4)
	{
		SDL_RenderDrawPoint(g_pRenderer, SCREEN_WIDTH / 2, i);
	}

	//Update screen
	SDL_RenderPresent(g_pRenderer);
}
void Close()
{
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


	//Deallocate surface
	SDL_FreeSurface(g_pScreenSurface);
	g_pScreenSurface = nullptr;

	//Destroy window
	SDL_DestroyWindow(g_pWindow);
	g_pWindow = nullptr;

	//Quit SDL subsystems
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