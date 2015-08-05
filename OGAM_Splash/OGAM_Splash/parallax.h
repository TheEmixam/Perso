#ifndef _PARALLAX_H_INCLUDED
#define _PARALLAX_H_INCLUDED


#include "vec2.h"
class TCamera;
class TCaillou;
class TGfxTexture;

class TParallax
{
public:
	TParallax();

	void move(TGfxVec2 tDep, TCamera *pCam);
	void render();
	void setPos(TGfxVec2 tPos){ m_tPos = tPos; }
	void setDepth(float fDepth){ m_fDepth = fDepth; }
	void setTexture(TGfxTexture* pTexture){ m_pTexture = pTexture; }
	float getDepth(){ return m_fDepth; }
	TGfxVec2 m_tPos;
private:
	float m_fDepth;
	TGfxTexture * m_pTexture;
};

#endif