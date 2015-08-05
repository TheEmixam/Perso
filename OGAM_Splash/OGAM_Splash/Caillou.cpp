#include "caillou.h"
#include <SDL.h>
#include "base.h"
#include "BounceZone.h"
#include "speedParticle.h"




TCaillou::TCaillou(){
	m_tDest = TGfxVec2(0, 0);
	m_tGrav = TGfxVec2(0, -0.1f);
	m_tPos = TGfxVec2(20, BASE_HAUTEUR);
	m_iRadius = 10;
}

bool TCaillou::move(TBounceZone *tBZone, TGfxVec2 *sortie)
{
	m_tDest += m_tGrav;
	TGfxVec2 newPos = m_tPos + m_tDest;
	if (tBZone != nullptr){
		if (newPos.y - m_iRadius < tBZone->m_tPos.y){
			if (newPos.x + m_iRadius > tBZone->m_tPos.x - tBZone->getRadius() && newPos.x - m_iRadius < tBZone->m_tPos.x + tBZone->getRadius()){
				TGfxVec2 vecNormale = TGfxVec2(0, 1);
				TGfxVec2 rebond = -(m_tDest.DotProduct(vecNormale)*vecNormale) * 2;
				m_tDest += rebond;

				newPos.y = tBZone->m_tPos.y + m_iRadius;
				float ratio = 1 - (pow(newPos.x - tBZone->m_tPos.x, 2) / (tBZone->getRadius()*tBZone->getRadius()));
				ratio = (ratio < MIN_INTENSITE_REBOND) ? MIN_INTENSITE_REBOND : ratio;
				m_tDest = m_tDest * ratio;
				//newPos += m_tDest;

				*sortie = newPos - m_tPos;

				m_tPos = newPos;

				return true;
			}
		}
	}
	*sortie = newPos - m_tPos;

	m_tPos = newPos;

	return false;
}

void TCaillou::addForce(TGfxVec2 tForce){
	m_tDest += tForce;
}

void TCaillou::render(){
	SDL_Rect t = { m_tPos.x - m_iRadius, m_tPos.y - m_iRadius, m_iRadius * 2, m_iRadius * 2 };
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(g_pRenderer, &t);
}


