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
	m_dAngle = 0.0;
	m_pRotationCenter = nullptr;
	m_tFlip = SDL_FLIP_NONE;
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
	if (m_pRotationCenter != nullptr) SDL_Point tRotation = { m_tCut.x + m_pRotationCenter->x, m_tCut.x + m_pRotationCenter->x };
	m_pTexture->render(m_iPosX, m_iPosY, &m_tCut, m_dAngle, m_pRotationCenter, m_tFlip);
}