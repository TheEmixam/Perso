#include "camera.h"
#include "graphique.h"
#include "caillou.h"
#include "BounceZone.h"
#include "base.h"
#include "parallax.h"
#include "speedParticle.h"

TCamera::TCamera(TCaillou *pCaillou, TBounceZone *pBounce[], TParallax *pParallax, TSpeedParticle * pParticle){
	m_pCaillou = pCaillou;
	m_pBounce = pBounce;
	m_pParallax = pParallax;
	m_pParticle = pParticle;
}
void TCamera::updateCam()
{
	m_tPos = TGfxVec2(m_pCaillou->m_tPos.x - SCREEN_WIDTH / 2, 0);
	TGfxVec2 oldPos;

	for (int i = 0; i < NB_PARALLAX; i++){
		if (m_pParallax[i].getDepth() >= 1){
			oldPos = m_pParallax[i].m_tPos;
			m_pParallax[i].m_tPos = TGfxVec2(oldPos.x, SCREEN_HEIGHT - oldPos.y) - m_tPos;
			m_pParallax[i].render();
			m_pParallax[i].m_tPos = oldPos;
		}
	}

	int heightOmbre = 10;
	SDL_Rect ombre = { SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT - (BASE_HAUTEUR + heightOmbre / 2), 20, heightOmbre / 2 };
	SDL_SetRenderDrawColor(g_pRenderer, 0x00, 0x00, 0x00, 0xDF);
	SDL_RenderFillRect(g_pRenderer, &ombre);

	for (int i = 0; i < TBounceZone::m_iMaxZones; i++){
		if (m_pBounce[i] != nullptr){
			oldPos = m_pBounce[i]->m_tPos;
			m_pBounce[i]->m_tPos = TGfxVec2(oldPos.x, SCREEN_HEIGHT - oldPos.y) - m_tPos;
			m_pBounce[i]->render();
			m_pBounce[i]->m_tPos = oldPos;
		}
	}

	oldPos = m_pParticle->getPos();
	m_pParticle->setGlobalPos(TGfxVec2(oldPos.x, SCREEN_HEIGHT - oldPos.y) - m_tPos);
	m_pParticle->render();
	m_pParticle->setGlobalPos(oldPos);

	oldPos = m_pCaillou->m_tPos;
	m_pCaillou->m_tPos = TGfxVec2(oldPos.x, SCREEN_HEIGHT - oldPos.y) - m_tPos;
	m_pCaillou->render();
	m_pCaillou->m_tPos = oldPos;

	oldPos = m_pParallax[2].m_tPos;
	m_pParallax[2].m_tPos = TGfxVec2(oldPos.x, SCREEN_HEIGHT - (oldPos.y-(m_pParallax[2].getHeight() - BASE_HAUTEUR))) - m_tPos;
	m_pParallax[2].setBlendMode(SDL_BLENDMODE_BLEND);
	m_pParallax[2].setAlpha(0xA3);
	SDL_Rect clip = { 0, (m_pParallax[2].getHeight() - BASE_HAUTEUR), m_pParallax[2].getWidth(), BASE_HAUTEUR };
	m_pParallax[2].render(&clip);
	m_pParallax[2].m_tPos = oldPos;
	m_pParallax[2].setBlendMode(SDL_BLENDMODE_NONE);


	ombre = { SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT - (BASE_HAUTEUR), 20, heightOmbre / 2 };
	SDL_SetRenderDrawColor(g_pRenderer, 0x00, 0x00, 0x00, 0xDF);
	//SDL_RenderFillRect(g_pRenderer, &ombre);

	for (int i = 0; i < NB_PARALLAX; i++){
		if (m_pParallax[i].getDepth() < 1){
			oldPos = m_pParallax[i].m_tPos;
			m_pParallax[i].m_tPos = TGfxVec2(oldPos.x, SCREEN_HEIGHT - oldPos.y) - m_tPos;
			m_pParallax[i].render();
			m_pParallax[i].m_tPos = oldPos;
		}
	}
}
