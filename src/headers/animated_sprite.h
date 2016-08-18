//Animated sprite header

#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <vector>
#include <string>

#include "sprite.h"
#include "globals.h"

class Graphics;

class AnimatedSprite : public Sprite
{
	public:
		AnimatedSprite();
		AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
				float posX, float posY, float timeToUpdate);

		void playAnimation(std::string animation, bool once = false); //bool once determines if anim plays once or not
		void update(int elapsedTime); //Updates the animated sprite
		void draw(Graphics &graphics, int x, int y); //Draws animated sprite
		virtual void setupAnimations(); //Sets up all animations for a sprite

	protected:
		double timeToUpdate;
		bool currentAnimationOnce;
		std::string currentAnimation;

		void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset); //Add animation
		void resetAnimations(); //Reset animation
		void stopAnimation(); //stops current animation
		void setVisible(bool visible); //Set visibility of sprite
		virtual void animationDone(std::string currentAnimation); //Logic that happens when an anim ends

	private:
		std::map<std::string, std::vector<SDL_Rect> > animations;
		std::map<std::string, Vector2> offsets;

		int frameIndex;
		double timeElapsed;
		bool visible;

};


#endif
