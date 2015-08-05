#include "BounceZone.h"
#include <SDL.h>
#include "base.h"


int TBounceZone::m_iCount = 0;

TBounceZone::TBounceZone(int x, int radius){
	m_tPos = TGfxVec2(x, BASE_HAUTEUR);
	m_iRadius = radius;
}

void TBounceZone::render(){
	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(g_pRenderer, m_tPos.x - m_iRadius, m_tPos.y, m_tPos.x + m_iRadius, m_tPos.y);
}