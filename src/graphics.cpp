//Graphics class implementation
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graphics.h"
#include "globals.h"

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(256, 224, SDL_WINDOW_OPENGL, &this->window, &this->renderer);
	SDL_SetWindowTitle(this->window, "Cave Story Remake");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_RenderSetLogicalSize(this->renderer, 256, 224); //Set render resolution to SNES resolution
	SDL_SetWindowSize(this->window, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT); //Resize window to preferred resolution
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath)
{
	if (this->spriteSheets.count(filePath) == 0) //Loads then returns sprites if not loaded yet, returns loaded sprites if loaded
	{
		this->spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle)
{
	SDL_RenderCopy(this->renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip()
{
	SDL_RenderPresent(this->renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(this->renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
	return this->renderer;
}

