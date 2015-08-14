#include "speedParticle.h"
#include "vec2.h"
#include <SDL.h>
#include "base.h"

TSpeedParticle::TSpeedParticle(){
	for (int i = 0; i < m_iNbParticle; i++){
		m_tPositions[i] = TGfxVec2(1,0);
	}
}

void TSpeedParticle::move(TGfxVec2 tPos){
	int x, y1 , y2;
	for (int i = m_iNbParticle - 1; i > 0; i--){
		m_tPositions[i] = m_tPositions[(i - 1)];
		m_pRadius[i] = (m_iNbParticle - i) * ((float)m_iBaseRadius / m_iNbParticle);
		m_pColor[i][0] = m_pColor[(i-1)][0];
		m_pColor[i][1] = m_pColor[(i-1)][1];
		m_pColor[i][2] = m_pColor[(i-1)][2];
	}
	m_tPositions[0] = tPos + TGfxVec2(-m_iBaseRadius/2,m_iBaseRadius/2);
	m_pRadius[0] = m_iBaseRadius;
	int r=0;
	int g=0;
	int b=0;
	while ((r + g + b) / 3.f < 200){
		r = (rand() % 256);
		g = (rand() % 256);
		b = (rand() % 256);
	}
	m_pColor[0][0] = r;
	m_pColor[0][1] = g;
	m_pColor[0][2] = b;
}

void TSpeedParticle::render(){
	for (int i = 0; i < m_iNbParticle - 1; i++){
		SDL_SetRenderDrawColor(g_pRenderer, m_pColor[i][0], m_pColor[i][1], m_pColor[i][2], 0xFF);
		SDL_Rect rect = { m_tPositions[i].x, m_tPositions[i].y, m_pRadius[i], m_pRadius[i] };
		SDL_RenderFillRect(g_pRenderer, &rect);
	}
}

void TSpeedParticle::setGlobalPos(TGfxVec2 tPos){
	TGfxVec2 tDep = tPos - m_tPositions[0];
	for (int i = 0; i < m_iNbParticle; i++){
		m_tPositions[i] += tDep * TGfxVec2(1,0);
		m_tPositions[i].y = SCREEN_HEIGHT - m_tPositions[i].y;
	}
}