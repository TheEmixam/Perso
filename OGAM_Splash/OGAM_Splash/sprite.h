#ifndef _SPRITE_H_INCLUDED
#define _SPRITE_H_INCLUDED
#include <SDL_types.h>

class TGfxTexture;

struct TSpriteInfo
{
	//Cut
	SDL_Rect Cut;

	//Position
	int X;
	int Y;

	//Rotation
	double Angle;
	SDL_Point* RotationCenter;

	//Flip
	SDL_RendererFlip Flip;

	//Alpha
	SDL_BlendMode BlendMode;
	Uint8 Alpha;

	//Color
	Uint8 Color[3];
};

class TGfxSprite
{
public:
	TGfxSprite();
	~TGfxSprite();

	bool loadFromTexture(TGfxTexture* pTexture, SDL_Rect tCut);

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue){ m_tInfos.Color[0] = red; m_tInfos.Color[1] = green; m_tInfos.Color[2] = blue; };
	//Set blending
	void setBlendMode(SDL_BlendMode blending){ m_tInfos.BlendMode = blending; }
	//Set alpha modulation
	void setAlpha(Uint8 alpha){ m_tInfos.Alpha = alpha; }
	//Set rotation
	void rotate(double angle, SDL_Point* center){ m_tInfos.Angle = angle; m_tInfos.RotationCenter = center; }
	//Flip
	void flip(SDL_RendererFlip flip = SDL_FLIP_NONE){ m_tInfos.Flip = flip; }

	void free();

	void render();

	/* Get /--\ Set */

	void setCut(const SDL_Rect tCut){ m_tInfos.Cut = tCut; }
	void setPos(const int x, const int y){ m_tInfos.X = x; m_tInfos.Y = y; }

	const TSpriteInfo getInfos()const{ return m_tInfos; }

private:
	TGfxTexture* m_pTexture;

	TSpriteInfo m_tInfos;
	
};

#endif
