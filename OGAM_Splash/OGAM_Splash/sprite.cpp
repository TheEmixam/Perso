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
	m_tInfos = { SDL_Rect(), 0, 0, 0.0, nullptr, SDL_FLIP_NONE, SDL_BLENDMODE_NONE, 0, { 0xFF, 0xFF, 0xFF } };
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
		m_tInfos.Cut = tCut;
		
		if (SDL_GetTextureBlendMode(m_pTexture->getTexture(), &m_tInfos.BlendMode)){
			printf("Error getting the blendmode! SDL_Error: %s\n", SDL_GetError());
		}
		if (SDL_GetTextureAlphaMod(m_pTexture->getTexture(), &m_tInfos.Alpha)){
			printf("Error getting the blendmode! SDL_Error: %s\n", SDL_GetError());
		}
		

		return true;
	}
	return false;
}

void TGfxSprite::free()
{
	if (m_pTexture != nullptr)
	{
		m_tInfos.X = 0;
		m_tInfos.Y = 0;
	}
}
void TGfxSprite::render()
{
	if (m_tInfos.RotationCenter != nullptr) SDL_Point tRotation = { m_tInfos.Cut.x + m_tInfos.RotationCenter->x, 
		m_tInfos.Cut.x + m_tInfos.RotationCenter->x };

	SDL_BlendMode blendMode = SDL_BLENDMODE_NONE;
	if (SDL_GetTextureBlendMode(m_pTexture->getTexture(), &blendMode) && m_tInfos.BlendMode){
		printf("Error getting the blendmode! SDL_Error: %s\n", SDL_GetError());
	}
	else if(m_tInfos.BlendMode != blendMode){
		m_pTexture->setBlendMode(m_tInfos.BlendMode);
	}
	Uint8 alpha = 0;
	if (SDL_GetTextureAlphaMod(m_pTexture->getTexture(), &alpha)){
		printf("Error getting the alpha! SDL_Error: %s\n", SDL_GetError());
	}
	else if(m_tInfos.Alpha != alpha){
		m_pTexture->setAlpha(m_tInfos.Alpha);
	}
	Uint8 r = 0;
	Uint8 g = 0;
	Uint8 b = 0;
	if (SDL_GetTextureColorMod(m_pTexture->getTexture(), &r, &g, &b)){
		printf("Error getting the color! SDL_Error: %s\n", SDL_GetError());
	}
	else if (m_tInfos.Color[0] != r || m_tInfos.Color[1] != g || m_tInfos.Color[2] != b){
		m_pTexture->setColor(m_tInfos.Color[0], m_tInfos.Color[1], m_tInfos.Color[2]);
	}

	m_pTexture->render(m_tInfos.X, m_tInfos.Y, &m_tInfos.Cut, m_tInfos.Angle, m_tInfos.RotationCenter, m_tInfos.Flip);
	
	m_pTexture->setBlendMode(blendMode);
	m_pTexture->setAlpha(alpha);
	m_pTexture->setColor(r, g, b);
	
}