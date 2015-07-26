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

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y);

	//Gets image dimensions
	int getWidth(){ return m_iWidth; }
	int getHeight(){ return m_iHeight; }

private:
	//The actual hardware texture
	SDL_Texture* m_pTexture;

	//Image dimensions
	int m_iWidth;
	int m_iHeight;
};

#endif