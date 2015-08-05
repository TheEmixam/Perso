#ifndef _CAILLOU_H
#define _CAILLOU_H

#include "graphique.h"
class TBounceZone;

class TCaillou : public TGraphique
{
public:
	TCaillou();

	bool move(TBounceZone *tBZone, TGfxVec2 *sortie);

	void addForce(TGfxVec2 tForce);

	void render();

	TGfxVec2 getDest(){ return m_tDest; }
private:
	TGfxVec2 m_tDest;
	TGfxVec2 m_tGrav;
	int m_iRadius;
};


#endif