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
	m_pressedKeys[LEFT] = false;
	m_pressedKeys[RIGHT] = false;
	m_pressedKeys[JUMP] = false;
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
		}

		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_a: 
				m_pressedKeys[LEFT] = true;
				break;
			case SDLK_d: 
					m_pressedKeys[RIGHT] = true;
				break;
			case SDLK_SPACE:
					m_pressedKeys[JUMP] = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
					m_pressedKeys[LEFT] = false;
				break;
			case SDLK_d:
					m_pressedKeys[RIGHT] = false;
				break;
			}
			break;
		}
	}
	Process(game);
}

void
InputHandler::Process(Game& game)
{
	if (m_pressedKeys[LEFT])
	{
		game.MovePlayerLeft();
	}
	else if (m_pressedKeys[RIGHT])
	{
		game.MovePlayerRight();
	}
	else
	{
		game.StopMovement();
	}

	if (m_pressedKeys[JUMP])
	{
		game.PlayerJump();
		m_pressedKeys[JUMP] = false;
	}
}
