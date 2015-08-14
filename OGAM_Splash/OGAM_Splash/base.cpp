#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"
#include "texture.h"
#include "sprite.h"
#include "vec2.h"
#include "graphique.h"
#include "camera.h"
#include "BounceZone.h"
#include "caillou.h"
#include "parallax.h"
#include "speedParticle.h"



SDL_Window* g_pWindow = nullptr;
SDL_Renderer* g_pRenderer = nullptr;
//Globally used font
TTF_Font *g_pFont = nullptr;
//Game Controller 1 handler
SDL_Joystick* g_pGameController = nullptr;
SDL_Haptic* g_pControllerHaptic = nullptr;
//The sound effects that will be used
Mix_Chunk *gHigh = NULL;

//Normalized direction
int xDir = 0;
int yDir = 0;

TCaillou g_tCaillou;
TGfxTexture g_tCaillouTexture;
TBounceZone * g_pBZones[TBounceZone::m_iMaxZones];
TBounceZone * g_pActualZone = nullptr;
TCamera * pCam;


TParallax g_pParallax[NB_PARALLAX];
TGfxTexture g_pParallaxTexture[NB_PARALLAX];
TSpeedParticle g_tParticle;

TGfxTexture g_tDistance;
TGfxTexture g_tSpeed;
TGfxTexture g_tPerdu;

TGfxTexture g_tWordsTexture;
TGfxSprite g_tWords;




bool LoadMedia()
{
	//Loading success flag
	bool bSuccess = true;
	
	//Open the font
	g_pFont = TTF_OpenFont("fonts/zx.ttf", 46);
	if (g_pFont == nullptr)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		bSuccess = false;
	}
	else
	{
		//TTF_SetFontStyle(g_pFont, TTF_STYLE_BOLD);
		//Render text
		SDL_Color textColor = { 255, 255, 255 };
		if (!g_tDistance.loadFromRenderedText("Distance", textColor))
		{
			printf("Failed to render text texture!\n");
			bSuccess = false;
		}
		if (!g_tSpeed.loadFromRenderedText("Distance", textColor))
		{
			printf("Failed to render text texture!\n");
			bSuccess = false;
		}
	}


	gHigh = Mix_LoadWAV("sound/high.wav");
	if (gHigh == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		bSuccess = false;
	}

	if (!g_tCaillouTexture.loadFromFile("img/rock.png")){
		printf("Error caillou\n");
		bSuccess = false;
	}
	else{
		
		SDL_Rect cut = { 0, 0, g_tCaillou.getRadius() * 2, g_tCaillou.getRadius() * 2};
		g_tCaillou.m_pSprite = new TGfxSprite();
		g_tCaillou.m_pSprite->loadFromTexture(&g_tCaillouTexture, cut);
	}

	if (!g_pParallaxTexture[0].loadFromFile("img/sky_day.png"))
	{
		printf("Error loading texture\n");
		bSuccess = false;
	}
	if (!g_pParallaxTexture[1].loadFromFile("img/mountains_day.png"))
	{
		printf("Error loading texture\n");
		bSuccess = false;
	}
	if (!g_pParallaxTexture[2].loadFromFile("img/water_day.png"))
	{
		printf("Error loading texture\n");
		bSuccess = false;
	}
	if (!g_pParallaxTexture[3].loadFromFile("img/grass.png"))
	{
		printf("Error loading texture\n");
		bSuccess = false;
	}
	if (!g_tWordsTexture.loadFromFile("img/words2.png"))
	{
		printf("Error words \n");
		bSuccess = false;
	}
	SDL_Rect cut = { 200, 0, 200, 32 };
	g_tWords.loadFromTexture(&g_tWordsTexture, cut);
	g_tWords.setPos(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT/2);
	//g_tWords.setBlendMode(SDL_BLENDMODE_NONE);
	g_tWords.setColor(0xFF, 0xFF, 0xFF);
	
	g_pParallax[0].setTexture(&g_pParallaxTexture[0]);
	g_pParallax[1].setTexture(&g_pParallaxTexture[1]);
	g_pParallax[2].setTexture(&g_pParallaxTexture[2]);
	g_pParallax[3].setTexture(&g_pParallaxTexture[3]);

	g_pParallax[0].setDepth(12);
	g_pParallax[1].setDepth(6);
	g_pParallax[2].setDepth(1);
	g_pParallax[3].setDepth(0.8);

	

	

	g_tCaillou.addForce(TGfxVec2(4, 4));
	pCam = new TCamera(&g_tCaillou, g_pBZones, g_pParallax, &g_tParticle);
	pCam->updateCam();
	for (int i = 0; i < NB_PARALLAX; i++){
		g_pParallax[i].setPos(pCam->m_tPos);
	}
	g_pParallax[0].setPos(TGfxVec2(g_pParallax[0].m_tPos.x, 200));
	g_pParallax[1].setPos(TGfxVec2(g_pParallax[1].m_tPos.x, 100));

	return bSuccess;
}
void Update()
{
	//Clear screen
	SDL_SetRenderDrawBlendMode(g_pRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_pRenderer);

	//Calculate angle
	double joystickAngle = atan2((double)yDir, (double)xDir) * (180.0 / M_PI);

	//printf("Joystick angle: %f\n", joystickAngle);
	TGfxVec2 tDeplacement;
	EZoneQuality result = g_tCaillou.move(g_pActualZone, &tDeplacement);
	if (result != EZoneQuality_Amount){
		g_pActualZone = nullptr;
		g_tWords.setCut(g_pZoneQualityCut[result]);
	}

	for (int i = 0; i < NB_PARALLAX; i++)
	{
		g_pParallax[i].move(tDeplacement, pCam);
	}
	g_tParticle.move(g_tCaillou.m_tPos);
	
	pCam->updateCam();

	char text[20];
	sprintf_s(text, 20, "Distance : %.2f m", g_tCaillou.m_tPos.x / 1000);
	SDL_Color textColor = { 255, 255, 255 };
	g_tDistance.print(text, textColor);

	char text2[20];
	sprintf_s(text2, 20, "Speed : %.2f m/s", (g_tCaillou.getDest().x / 1000) * 60);
	g_tSpeed.print(text2, textColor);
	
	g_tWords.render();
	g_tDistance.render(10, 0);
	g_tSpeed.render(10, g_tDistance.getHeight());
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
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				//Play high sound effect
			case SDLK_1:
				Mix_PlayChannel(-1, gHigh, 0);
				break;
			case SDLK_SPACE:
				if (g_pActualZone == nullptr && g_tCaillou.m_tPos.y - g_tCaillou.getRadius() > BASE_HAUTEUR){
					g_pBZones[TBounceZone::m_iCount++] = new TBounceZone(g_tCaillou.m_tPos.x, 100);
					g_pActualZone = g_pBZones[TBounceZone::m_iCount - 1];
				}
				break;
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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_AUDIO) < 0)
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
		g_pWindow = SDL_CreateWindow("Ricochet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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
	//Free the sound effects
	Mix_FreeChunk(gHigh);
	gHigh = NULL;

	//Free loaded images

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
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}