//Graphics class header


struct SDL_Window;
struct SDL_Renderer;

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

class Graphics
{
	public:
		Graphics();
		~Graphics();

		SDL_Surface* loadImage(const std::string &filePath);
		void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle); //Draws texture to a part of the screen
		void flip(); //Renders everything to screen
		void clear(); //Clears the screen
		SDL_Renderer* getRenderer() const; //Returns the renderer

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::map<std::string, SDL_Surface*> spriteSheets;
};




#endif
