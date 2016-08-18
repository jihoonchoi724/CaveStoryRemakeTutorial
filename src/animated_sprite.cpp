//Animated sprite class implementation

#include "sprite.h"
#include "animated_sprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}
AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
		int width, int height, float posX, float posY, float timeToUpdate) :
				Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
				timeToUpdate(timeToUpdate), currentAnimationOnce(false), frameIndex(0), timeElapsed(0), visible(true),
				currentAnimation("")
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; ++i)
	{
		SDL_Rect newRect = { (i + x) * width, y, width, height};
		rectangles.push_back(newRect);
	}
	this->animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
	this->offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations()
{
	this->animations.clear();
	this->offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
	this->currentAnimationOnce = once;
	if (this->currentAnimation != animation)
	{
		this->currentAnimation = animation;
		this->frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible)
{
	this->visible = visible;
}

void AnimatedSprite::stopAnimation()
{
	this->frameIndex = 0;
	this->animationDone(this->currentAnimation);
}

void AnimatedSprite::update(int elapsedTime)
{
	Sprite::update();

	this->timeElapsed += elapsedTime;
	if (this->timeElapsed > this->timeToUpdate)
	{
		this->timeElapsed -= this->timeToUpdate;
		if (this->frameIndex < this->animations[this->currentAnimation].size() - 1)
		{
			this->frameIndex++;
		}
		else
		{
			if (this->currentAnimationOnce == true)
			{
				this->setVisible(false);
			}
			this->stopAnimation();
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect destinationRectangle;
	destinationRectangle.x = x + this->offsets[this->currentAnimation].x;
	destinationRectangle.y = y + this->offsets[this->currentAnimation].y;
	destinationRectangle.w = this->sourceRect.w;
	destinationRectangle.h = this->sourceRect.h;

	SDL_Rect sourceRect = this->animations[this->currentAnimation][this->frameIndex];
	graphics.blitSurface(this->spriteSheet, &sourceRect, &destinationRectangle);
}

void AnimatedSprite::animationDone(std::string currentAnimation)
{

}

void AnimatedSprite::setupAnimations()
{
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
}
