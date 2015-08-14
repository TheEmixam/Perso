#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "texture.h"
#include "base.h"

TGfxTexture::TGfxTexture()
{
	//Initialize
	m_pTexture = nullptr;
	m_iWidth = 0;
	m_iHeight = 0;
}
TGfxTexture::~TGfxTexture()
{
	//Deallocate
	free();
}

bool TGfxTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(g_pRenderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_iWidth = loadedSurface->w;
			m_iHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_pTexture = newTexture;
	return m_pTexture != nullptr;
}
bool TGfxTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(g_pFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, textSurface);
		if (m_pTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_iWidth = textSurface->w;
			m_iHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return m_pTexture != nullptr;
}

void TGfxTexture::print(std::string textureText, SDL_Color textColor){
	if (m_pTexture != nullptr){
		free();
		loadFromRenderedText(textureText, textColor);
	}
}

void TGfxTexture::free()
{
	//Free texture if it exists
	if (m_pTexture != nullptr)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
		m_iWidth = 0;
		m_iHeight = 0;
	}
}

void TGfxTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_iWidth, m_iHeight };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	
	//Render to screen
	SDL_RenderCopyEx(g_pRenderer, m_pTexture, clip, &renderQuad, angle, center, flip);
}


void TGfxTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(m_pTexture, red, green, blue);
}
void TGfxTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(m_pTexture, blending);
}
void TGfxTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(m_pTexture, alpha);
}