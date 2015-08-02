#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>

struct SDL_Texture;

//Texture wrapper class
class TGfxTexture
{
public:
	//Initializes variables
	TGfxTexture();

	//Deallocates memory
	~TGfxTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	//Set blending
	void setBlendMode(SDL_BlendMode blending);
	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Gets image dimensions
	int getWidth(){ return m_iWidth; }
	int getHeight(){ return m_iHeight; }
	SDL_Texture* getTexture()const{ return m_pTexture; }

private:
	//The actual hardware texture
	SDL_Texture* m_pTexture;

	//Image dimensions
	int m_iWidth;
	int m_iHeight;
};

#endif