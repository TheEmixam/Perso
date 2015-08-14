#include "BounceZone.h"
#include <SDL.h>
#include "base.h"

const char * g_pZoneQualityName[EZoneQuality_Amount] = { "Bad!!", "Meh", "Good", "Perfect!" };
const float g_pZoneQualityValue[EZoneQuality_Amount] = { 0.4f, 0.7f, 0.9f, 1.f };
const Uint8 g_pZoneQualityColor[EZoneQuality_Amount][3] = { {0xff,0x00,0x00}, {0xFF,0xFF,0x00}, {0x78,0xFF,0x00}, {0xFF,0xFF,0xFF} };
const SDL_Rect g_pZoneQualityCut[EZoneQuality_Amount] = { { 200, 32, 200, 32 }, { 0, 32, 200, 32 }, { 200, 0, 200, 32 }, { 0, 0, 200, 32 } };

int TBounceZone::m_iCount = 0;

TBounceZone::TBounceZone(int x, int radius){
	m_tPos = TGfxVec2(x, BASE_HAUTEUR);
	m_iRadius = radius;
}

void TBounceZone::render(){
	SDL_SetRenderDrawColor(g_pRenderer, g_pZoneQualityColor[EZoneQuality_Bad][0], g_pZoneQualityColor[EZoneQuality_Bad][1], g_pZoneQualityColor[EZoneQuality_Bad][2], 0xFF);
	SDL_RenderDrawLine(g_pRenderer, m_tPos.x, m_tPos.y, m_tPos.x + m_iRadius, m_tPos.y);

	for (int i = 0; i < EZoneQuality_Amount - 1; i++){
		SDL_SetRenderDrawColor(g_pRenderer, g_pZoneQualityColor[i+1][0], g_pZoneQualityColor[i+1][1], g_pZoneQualityColor[i+1][2], 0xFF);
		SDL_RenderDrawLine(g_pRenderer, m_tPos.x, m_tPos.y, m_tPos.x + m_iRadius - (g_pZoneQualityValue[i] * m_iRadius), m_tPos.y);
	}
}