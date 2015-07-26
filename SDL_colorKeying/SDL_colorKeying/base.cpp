#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "base.h"
#include "texture.h"

SDL_Window* g_pWindow = nullptr;
SDL_Surface* g_pScreenSurface = nullptr;
SDL_Surface* g_pStretchedSurface = nullptr;

SDL_Renderer* g_pRenderer = nullptr;

TGfxTexture* g_tFooTexture = new TGfxTexture();
TGfxTexture* g_tBackgroundTexture = new TGfxTexture();

bool LoadMedia()
{
	//Loading success flag
	bool bSuccess = true;

	//Load Foo' texture
	if (!g_tFooTexture->loadFromFile("img/foo.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		bSuccess = false;
	}

	//Load background texture
	if (!g_tBackgroundTexture->loadFromFile("img/background.png"))
	{
		printf("Failed to load background texture image!\n");
		bSuccess = false;
	}

	return bSuccess;
}
void Update()
{
	//Clear screen
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_pRenderer);

	//Render background texture to screen
	g_tBackgroundTexture->render(0, 0);

	//Render Foo' to the screen
	g_tFooTexture->render(240, 190);

	//Update screen
	SDL_RenderPresent(g_pRenderer);
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

	//Deallocate surface
	SDL_FreeSurface(g_pScreenSurface);
	g_pScreenSurface = nullptr;

	//Free loaded images
	g_tFooTexture->free();
	g_tBackgroundTexture->free();

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