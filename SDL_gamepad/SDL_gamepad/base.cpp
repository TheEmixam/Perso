#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include "base.h"
#include "texture.h"
#include "sprite.h"

SDL_Window* g_pWindow = nullptr;
SDL_Renderer* g_pRenderer = nullptr;
//Globally used font
TTF_Font *g_pFont = nullptr;
//Game Controller 1 handler
SDL_Joystick* g_pGameController = nullptr;
SDL_Haptic* g_pControllerHaptic = nullptr;

TGfxTexture gArrowTexture;

//Normalized direction
int xDir = 0;
int yDir = 0;




bool LoadMedia()
{
	//Loading success flag
	bool bSuccess = true;

	//Load arrow texture
	if (!gArrowTexture.loadFromFile("img/arrow.png"))
	{
		printf("Failed to load arrow texture!\n");
		bSuccess = false;
	}

	return bSuccess;
}
void Update()
{
	//Clear screen
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_pRenderer);

	//Calculate angle
	double joystickAngle = atan2((double)yDir, (double)xDir) * (180.0 / M_PI);

	//Correct angle
	if (xDir == 0 && yDir == 0)
	{
		joystickAngle = 0;
	}

	//Render joystick 8 way angle
	gArrowTexture.render((SCREEN_WIDTH - gArrowTexture.getWidth()) / 2, (SCREEN_HEIGHT - gArrowTexture.getHeight()) / 2, NULL, joystickAngle);

	SDL_RenderPresent(g_pRenderer);
}
bool Inputs(SDL_Event e)
{
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return true;
			break;
		case SDL_JOYAXISMOTION:
			//Motion on controller 0
			if (e.jaxis.which == 0)
			{
				//X axis motion
				if (e.jaxis.axis == 0)
				{
					//Left of dead zone
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE || e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						xDir = e.jaxis.value;
					}
					else
					{
						xDir = 0;
					}
				}
				//Y axis motion
				else if (e.jaxis.axis == 1)
				{
					//Below of dead zone
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE || e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						yDir = e.jaxis.value;
					}
					else
					{
						yDir = 0;
					}
				}
			}
			break;
		case SDL_JOYBUTTONDOWN:
			//Play rumble at 75% strenght for 500 milliseconds
			if (SDL_HapticRumblePlay(g_pControllerHaptic, 0.2f, 500) != 0)
			{
				printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
			}
			break;
		}
	}

	//Set texture based on current keystate
	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		printf("Up\n");
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		printf("Down\n");
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		printf("Left\n");
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		printf("Right\n");
	}
	const Uint8 joystick = SDL_JoystickGetButton(g_pGameController, SDL_CONTROLLER_BUTTON_B);
	if (joystick != 0){
		printf("%d\n", joystick);
		//Play rumble at 75% strenght for 500 milliseconds
		if (SDL_HapticRumblePlay(g_pControllerHaptic, 0.9f, 500) != 0)
		{
			printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
		}
	}
	
	return false;
}




bool Init()
{
	//Initialization flag
	bool bSuccess = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) < 0)
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

		//Check for joysticks
		if (SDL_NumJoysticks() < 1)
		{
			printf("Warning: No joysticks connected!\n");
		}
		else
		{
			//Load joystick
			g_pGameController = SDL_JoystickOpen(0);
			if (g_pGameController == nullptr)
			{
				printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get controller haptic device
				g_pControllerHaptic = SDL_HapticOpenFromJoystick(g_pGameController);
				if (g_pControllerHaptic == nullptr)
				{
					printf("Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError());
				}
				else
				{
					//Get initialize rumble
					if (SDL_HapticRumbleInit(g_pControllerHaptic) < 0)
					{
						printf("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
					}
				}
			}
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
	gArrowTexture.free();

	//Close game controller
	SDL_HapticClose(g_pControllerHaptic);
	SDL_JoystickClose(g_pGameController);
	g_pGameController = nullptr;
	g_pControllerHaptic = nullptr;

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