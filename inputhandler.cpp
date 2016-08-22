// COMP710 GP 2D Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);
	//assert(m_pGameController);

	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	// W02.1: Receive Input Events below... DONE
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT /*|| e.key.keysym.sym == SDLK_q*/)
		{
			game.Quit();
		}
		else if (e.type == SDL_JOYBUTTONDOWN)
		{
			// W02.3: Tell the game to fire a player bullet...
			if (e.jbutton.button == 10)
			{
				//game.FireSpaceShipBullet();
			}

			// W02.1: Tell the game to move the space ship left... DONE

			// W02.1: Tell the game to move the space ship right... DONE
		}
		switch (e.type)
		{
		case SDL_JOYBUTTONDOWN: 
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_a: game.MovePlayerLeft();
				break;
			case SDLK_d: game.MovePlayerRight();
				break;
			case SDLK_SPACE: game.PlayerJump();
				break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_a: game.StopMovement();
				break;
			case SDLK_d: game.StopMovement();
				break;
			}
			break;
		}
	}
}
