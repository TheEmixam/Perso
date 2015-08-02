#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "button.h"
#include "texture.h"

TButton::TButton(TGfxTexture* pTexture)
{
	m_tPosition.x = 0;
	m_tPosition.y = 0;

	m_eCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	m_pTexture = pTexture;
}

void TButton::setPosition(int x, int y)
{
	m_tPosition.x = x;
	m_tPosition.y = y;
}

void TButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < m_tPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > m_tPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < m_tPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > m_tPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			m_eCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				m_eCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				m_eCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				m_eCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

void TButton::render(SDL_Rect pSpriteClips[4])
{
	//Show current button sprite
	m_pTexture->render(m_tPosition.x, m_tPosition.y, &pSpriteClips[m_eCurrentSprite]);
}