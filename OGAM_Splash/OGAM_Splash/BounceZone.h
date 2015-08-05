#ifndef _BOUNCEZONE_H_INCLUDED
#define _BOUNCEZONE_H_INCLUDED

#include "graphique.h"

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