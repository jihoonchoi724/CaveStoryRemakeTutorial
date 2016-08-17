//Input class implementation

#include "input.h"

void Input::beginNewFrame() //Every new frame, keypresses are reset by this function
{
	this->pressedKeys.clear();
	this->releasedKeys.clear();
}

void Input::keyDownEvent(const SDL_Event& event) //Pressed keys
{
	this->pressedKeys[event.key.keysym.scancode] = true;
	this->heldKeys[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event& event)
{
	this->releasedKeys[event.key.keysym.scancode] = true;
	this->heldKeys[event.key.keysym.scancode] = false;
}

bool Input::wasKeyPressed(SDL_Scancode key) //Checks if a certain key was pressed during this  frame
{
	return this->pressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key) //Checks if a certain key was released during this frame
{
	return this->releasedKeys[key];
}

bool Input::isKeyHeld(SDL_Scancode key) //Checks if a certain key is being held during this frame
{
	return this->heldKeys[key];
}


