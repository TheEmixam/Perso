#include "parallax.h"
#include "vec2.h"
#include "caillou.h"
#include "base.h"
#include "camera.h"
#include "texture.h"


TParallax::TParallax(){
	m_fDepth = 1;
	m_tPos = TGfxVec2(0, 0);
	m_pTexture = nullptr;
}

void TParallax::move(TGfxVec2 tDep, TCamera *pCam){
	m_tPos.x += tDep.x - (tDep.x / m_fDepth);
	//m_tPos.x += (m_fDepth == 42)? 0 : tDep.x / m_fDepth;
	
	m_tPos.x = (m_tPos.x < pCam->m_tPos.x) ? m_tPos.x + m_pTexture->getWidth() : m_tPos.x;	
}
void TParallax::render(SDL_Rect* clip){
	if (m_pTexture != nullptr){
		m_pTexture->render(m_tPos.x, m_tPos.y - m_pTexture->getHeight(), clip);
		m_pTexture->render(m_tPos.x - m_pTexture->getWidth(), m_tPos.y - m_pTexture->getHeight(), clip);
	}
}


void TParallax::setAlpha(Uint8 alpha){
	m_pTexture->setAlpha(alpha);
}
void TParallax::setBlendMode(SDL_BlendMode blending){
	m_pTexture->setBlendMode(blending);
}

int TParallax::getHeight(){
	return m_pTexture->getHeight();
}
int TParallax::getWidth(){
	return m_pTexture->getWidth();
}