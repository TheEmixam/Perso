//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "base.h"

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			Loop(Update, Close);
		}
	}
	//Wait two seconds
	SDL_Delay(1000);
	return 0;
}