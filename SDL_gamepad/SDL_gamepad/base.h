#ifndef _BASE_H_INCLUDED
#define _BASE_H_INCLUDED

#include <string>
#include <SDL_ttf.h>

struct SDL_Window;
struct SDL_Surface;
class TGfxTexture;

bool Init();
bool LoadMedia();
void Loop(bool(*inputs)(SDL_Event e), void(*update)());
void Update();
bool Inputs(SDL_Event e);
void Close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);
SDL_Surface* loadSurface(std::string path);

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//Analog joystick dead zone (-32768 to 32767)
const int JOYSTICK_DEAD_ZONE = 8000;

//The window we'll be rendering to
extern SDL_Window* g_pWindow;
extern SDL_Renderer* g_pRenderer;
//Globally used font
extern TTF_Font* g_pFont;

#endif