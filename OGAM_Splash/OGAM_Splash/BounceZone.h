#ifndef _BOUNCEZONE_H_INCLUDED
#define _BOUNCEZONE_H_INCLUDED

#include "graphique.h"
#include <SDL_types.h>
struct SDL_Rect;

enum EZoneQuality
{
	EZoneQuality_Bad = 0,
	EZoneQuality_Meh,
	EZoneQuality_Good,
	EZoneQuality_Perfect,

	EZoneQuality_Amount,
};

extern const char * g_pZoneQualityName[EZoneQuality_Amount];
extern const float g_pZoneQualityValue[EZoneQuality_Amount];
extern const Uint8 g_pZoneQualityColor[EZoneQuality_Amount][3];
extern const SDL_Rect g_pZoneQualityCut[EZoneQuality_Amount];


class TBounceZone : public TGraphique
{
public:
	TBounceZone(int x, int radius);
	void render();

	int getRadius(){ return m_iRadius; }

	static int m_iCount;
	static const int m_iMaxZones = 50;
private:
	float m_iRadius;
};

#endif