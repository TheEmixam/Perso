#ifndef _GRAPHIQUE_H_INCLUDED
#define _GRAPHIQUE_H_INCLUDED
 

#include "vec2.h"
class TGfxSprite;

struct TGraphique
{
	TGfxVec2 m_tPos;
	TGfxSprite* m_pSprite;
};

#endif