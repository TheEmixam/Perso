#include "speedParticle.h"
#include "caillou.h"
#include <SDL.h>
#include "base.h"
#include "BounceZone.h"
#include "sprite.h"




TCaillou::TCaillou(){
	m_tDest = TGfxVec2(0, 0);
	m_tGrav = TGfxVec2(0, -0.1f);
	m_tPos = TGfxVec2(20, BASE_HAUTEUR);
	m_iRadius = 40;
}

EZoneQuality TCaillou::move(TBounceZone *tBZone, TGfxVec2 *sortie)
{
	m_tDest += m_tGrav;
	TGfxVec2 newPos = m_tPos + m_tDest;
	if (tBZone != nullptr){
		if (newPos.y - m_iRadius < tBZone->m_tPos.y && m_tPos.y > BASE_HAUTEUR){
			if (newPos.x + m_iRadius > tBZone->m_tPos.x - tBZone->getRadius() && newPos.x - m_iRadius < tBZone->m_tPos.x + tBZone->getRadius()){
				TGfxVec2 vecNormale = TGfxVec2(0, 1);
				TGfxVec2 rebond = -(m_tDest.DotProduct(vecNormale)*vecNormale) * 2;
				m_tDest += rebond;

				newPos.y = tBZone->m_tPos.y + m_iRadius;
				float ratio = 1 - (pow(newPos.x - tBZone->m_tPos.x, 2) / (tBZone->getRadius()*tBZone->getRadius()));

				int i;
				for (i = 0; i < EZoneQuality_Amount; i++){
					if (ratio < g_pZoneQualityValue[i]){
						printf(g_pZoneQualityName[i]);
						printf("\n");
						ratio = g_pZoneQualityValue[i];
						break;
					}
				}
				m_tDest = m_tDest * ratio;
				m_tDest += (ratio == 1) ? m_tDest * 0.5f : TGfxVec2(0,0);
				float angleMax = 20; //vecteur up
				float angleVect = 90 * (M_PI / 180) - atan2(m_tDest.x, m_tDest.y);
				if (angleVect> angleMax * (M_PI / 180)){
					float angle = -8 * (M_PI / 180);
					m_tDest = m_tDest.Rotate(angle * ratio);
					//m_tDest.x+= m_tDest.x*0.1f;
				}
				//newPos += m_tDest;

				*sortie = newPos - m_tPos;

				m_tPos = newPos;

				return EZoneQuality(i);
			}
		}
	}
	*sortie = newPos - m_tPos;

	m_tPos = newPos;

	if (m_tPos.y < BASE_HAUTEUR){
		m_tDest.y += -m_tDest.y * 0.3f;
		m_tDest.x += -m_tDest.x * 0.02f;
	}
	return EZoneQuality_Amount;
}

void TCaillou::addForce(TGfxVec2 tForce){
	m_tDest += tForce;
}

void TCaillou::render(){
	SDL_Rect t = { m_tPos.x - m_iRadius, m_tPos.y - m_iRadius, m_iRadius * 2, m_iRadius * 2 };
	//SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0x00, 0x00, 0xFF);
	//SDL_RenderFillRect(g_pRenderer, &t);
	m_pSprite->setPos(t.x, t.y);
	m_pSprite->render();
}


