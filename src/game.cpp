//Main game class implementation
#include <algorithm>
#include <SDL2/SDL.h>

#include "game.h"
#include "graphics.h"
#include "input.h"

namespace
{
	const int FPS = 60;
	const int MAX_FRAME_TIME = 6 * 1000 / FPS;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game()
{

}

void Game::gameLoop()
{
	Graphics graphics;
	SDL_Event event;
	Input input;

	this->player = AnimatedSprite(graphics, "Resources/Sprites/MyChar.png", 0, 0, 16, 16, 50, 50, 100);
	this->player.setupAnimations();
	this->player.playAnimation("RunLeft");


	int LAST_UPDATE_TIME = SDL_GetTicks();


	while(true)
	{
		input.beginNewFrame(); //Resets pressed keys

		if (SDL_PollEvent(&event)) //Polls SDL events
		{
			if (event.type == SDL_KEYDOWN) //Key was pressed
			{
				if (event.key.repeat == 0) //Makes sure no key is being held
				{
					input.keyDownEvent(event);
				}
			}

			else if (event.type == SDL_KEYUP) //Key was released
			{
				input.keyUpEvent(event);
			}

			else if (event.type == SDL_QUIT) //Exit window
			{
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) //Escape was pressed
		{
			return;
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics)
{
	graphics.clear();

	this->player.draw(graphics, 50, 50);
	graphics.flip();
}

void Game::update(float elapsedTime)
{
	this->player.update(elapsedTime);
}


