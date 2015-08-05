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
	if (m_fDepth < 1)
	{
		m_tPos.x = (m_tPos.x > pCam->m_tPos.x + SCREEN_WIDTH) ? m_tPos.x - m_pTexture->getWidth() : m_tPos.x;
	}
	else
	{
		m_tPos.x = (m_tPos.x < pCam->m_tPos.x) ? m_tPos.x + m_pTexture->getWidth() : m_tPos.x;
	}
}
void TParallax::render(){
	if (m_pTexture != nullptr){
		m_pTexture->render(m_tPos.x, m_tPos.y);
		m_pTexture->render(m_tPos.x - m_pTexture->getWidth(), m_tPos.y);
	}
}