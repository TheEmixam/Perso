#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

struct TGfxTexture;

class TGfxSprite
{
public:
	TGfxSprite();
	~TGfxSprite();

	bool loadFromTexture(TGfxTexture* pTexture, SDL_Rect tCut);

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue){ m_pTexture->setColor(red, green, blue); }
	//Set blending
	void setBlendMode(SDL_BlendMode blending){ m_pTexture->setBlendMode(blending); }
	//Set alpha modulation
	void setAlpha(Uint8 alpha){ m_pTexture->setAlpha(alpha); }
	//Set rotation
	void rotate(double angle, SDL_Point* center){ m_dAngle = angle; m_pRotationCenter = center; }
	//Flip
	void flip(SDL_RendererFlip flip = SDL_FLIP_NONE){ m_tFlip = flip; }

	void free();

	void render();

	/* Get /--\ Set */

	void setCut(const SDL_Rect tCut){ m_tCut = tCut; }
	void setX(const int x){ m_iPosX = x; }
	void setY(const int y){ m_iPosY = y; }

	const int getY()const{ return m_iPosY; }
	const int getX()const{ return m_iPosX; }

	const SDL_Rect& getCut(){ return m_tCut; }

private:
	TGfxTexture* m_pTexture;
	SDL_Rect m_tCut;

	int m_iPosX;
	int m_iPosY;

	double m_dAngle;
	SDL_Point* m_pRotationCenter;

	SDL_RendererFlip m_tFlip;
};

#endif
