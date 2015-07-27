#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "base.h"
#include "texture.h"
#include "sprite.h"

TGfxSprite::TGfxSprite()
{
	m_pTexture = nullptr;
	m_tCut = SDL_Rect();
	m_iPosX = 0;
	m_iPosY = 0;
}

TGfxSprite::~TGfxSprite()
{
	free();
}

bool TGfxSprite::loadFromTexture(TGfxTexture* pTexture, SDL_Rect tCut)
{
	if (pTexture != nullptr)
	{
		m_pTexture = pTexture;
		m_tCut = tCut;

		return true;
	}
	return false;
}

void TGfxSprite::free()
{
	if (m_pTexture != nullptr)
	{
		m_iPosX = 0;
		m_iPosY = 0;
	}
}

void TGfxSprite::render()
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {m_iPosX, m_iPosY, m_tCut.w, m_tCut.h};
	
	SDL_RenderCopy(g_pRenderer, m_pTexture->getTexture(), &m_tCut, &renderQuad);
}