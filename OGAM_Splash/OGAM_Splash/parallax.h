#ifndef _PARALLAX_H_INCLUDED
#define _PARALLAX_H_INCLUDED

#include <SDL_blendmode.h>
#include <SDL_types.h>
#include "vec2.h"
class TCamera;
class TCaillou;
class TGfxTexture;

struct SDL_Rect;


class TParallax
{
public:
	TParallax();

	void move(TGfxVec2 tDep, TCamera *pCam);
	void render(SDL_Rect* clip = nullptr);
	void setPos(TGfxVec2 tPos){ m_tPos = tPos; }
	void setDepth(float fDepth){ m_fDepth = fDepth; }
	void setTexture(TGfxTexture* pTexture){ m_pTexture = pTexture; }
	void setAlpha(Uint8 alpha);
	void setBlendMode(SDL_BlendMode blending);
	float getDepth(){ return m_fDepth; }
	int getHeight();
	int getWidth();
	TGfxVec2 m_tPos;
private:
	float m_fDepth;
	TGfxTexture * m_pTexture;
};

#endif