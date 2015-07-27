#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

struct TGfxTexture;

class TGfxSprite
{
public:
	TGfxSprite();
	~TGfxSprite();

	bool loadFromTexture(TGfxTexture* pTexture, SDL_Rect tCut);

	void free();

	void render();

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
};

#endif
