#ifndef _BUTTON_H_INCLUDED
#define _BUTTON_H_INCLUDED

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

class TGfxTexture;

enum EButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

//The mouse button
class TButton
{
public:
	//Initializes internal variables
	TButton(TGfxTexture* pTexture);

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render(SDL_Rect pSpriteClips[4]);

private:
	//Top left position
	SDL_Point m_tPosition;

	//Currently used global sprite
	EButtonSprite m_eCurrentSprite;

	TGfxTexture* m_pTexture;
};

#endif
