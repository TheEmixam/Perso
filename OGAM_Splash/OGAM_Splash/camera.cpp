#include "camera.h"
#include "graphique.h"
#include "caillou.h"
#include "BounceZone.h"
#include "base.h"
#include "parallax.h"

TCamera::TCamera(TCaillou *pCaillou, TBounceZone *pBounce[], TParallax *pParallax){
	m_pCaillou = pCaillou;
	m_pBounce = pBounce;
	m_pParallax = pParallax;
}
void TCamera::updateCam()
{
	m_tPos = TGfxVec2(m_pCaillou->m_tPos.x - SCREEN_WIDTH / 2, 0);
	TGfxVec2 oldPos;

	for (int i = 0; i < NB_PARALLAX; i++){
		if (m_pParallax[i].getDepth() > 0){
			oldPos = m_pParallax[i].m_tPos;
			m_pParallax[i].m_tPos = TGfxVec2(oldPos.x, oldPos.y) - m_tPos;
			m_pParallax[i].render();
			m_pParallax[i].m_tPos = oldPos;
		}
	}

	for (int i = 0; i < TBounceZone::m_iMaxZones; i++){
		if (m_pBounce[i] != nullptr){
			oldPos = m_pBounce[i]->m_tPos;
			m_pBounce[i]->m_tPos = TGfxVec2(oldPos.x, SCREEN_HEIGHT - oldPos.y) - m_tPos;
			m_pBounce[i]->render();
			m_pBounce[i]->m_tPos = oldPos;
		}
	}

	oldPos = m_pCaillou->m_tPos;
	m_pCaillou->m_tPos = TGfxVec2(oldPos.x, SCREEN_HEIGHT - oldPos.y) - m_tPos;
	m_pCaillou->render();
	m_pCaillou->m_tPos = oldPos;

	for (int i = 0; i < NB_PARALLAX; i++){
		if (m_pParallax[i].getDepth() < 0){
			oldPos = m_pParallax[i].m_tPos;
			m_pParallax[i].m_tPos = TGfxVec2(oldPos.x, oldPos.y) - m_tPos;
			m_pParallax[i].render();
			m_pParallax[i].m_tPos = oldPos;
		}
	}
}
