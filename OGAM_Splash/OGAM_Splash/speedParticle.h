#ifndef _SPEEDPARTICLE_H
#define _SPEEDPARTICLE_H

class TGfxVec2;

class TSpeedParticle
{
public:
	TSpeedParticle();
	void move(TGfxVec2 tDep);
	void render();

	static const int m_iNbParticle = 10;
private:
	TGfxVec2 m_tPositions[m_iNbParticle];
};


#endif