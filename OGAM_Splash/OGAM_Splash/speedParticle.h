#ifndef _SPEEDPARTICLE_H
#define _SPEEDPARTICLE_H

#include "vec2.h"

class TSpeedParticle
{
public:
	TSpeedParticle();
	void move(TGfxVec2 tPos);
	void render();
	void setGlobalPos(TGfxVec2 tPos);

	TGfxVec2 getPos(){ return m_tPositions[0]; }

	static const int m_iNbParticle = 30;
	static const int m_iBaseRadius = 18;
private:
	TGfxVec2 m_tPositions[m_iNbParticle];
	float m_pRadius[m_iNbParticle];
	int m_pColor[m_iNbParticle][3];
};


#endif