//Sprite class implementation

#include <iostream>
#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite(){}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY) :
				x(posX),
				y(posY)
{
	this->sourceRect.x = sourceX;
	this->sourceRect.y = sourceY;
	this->sourceRect.w = width;
	this->sourceRect.h = height;

	this->spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->spriteSheet == NULL)
	{
		std::cout << "Error: Unable to load image" << std::endl;
	}
}

Sprite::~Sprite(){}

void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect destinationRectangle = { x, y, this->sourceRect.w, this->sourceRect.h};
	graphics.blitSurface(this->spriteSheet, &this->sourceRect, &destinationRectangle);
}

void Sprite::update(){}



