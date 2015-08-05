#ifndef _CAMERA_H_INCLUDED
#define _CAMERA_H_INCLUDED

#include "graphique.h"

class TCaillou;
class TBounceZone;
class TParallax;

class TCamera : public TGraphique
{
public:
	TCamera(TCaillou *pCaillou, TBounceZone *pBounce[], TParallax *pParallax);
	void updateCam();

private:
	TCaillou * m_pCaillou;
	TBounceZone ** m_pBounce;
	TParallax * m_pParallax;
};

#endif
