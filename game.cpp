// COMP710 GP 2D Framework

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "player.h"
#include "tile.h"

// Library includes:
#include <cassert>
#include <SDL.h>

// Static Members:
Game* Game::sm_pInstance = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
	: m_pBackBuffer(0)
	, m_pInputHandler(0)
	, m_looping(true)
	, m_executionTime(0)
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_FPS(0)
	, m_numUpdates(0)
	, m_lastTime(0)
	, m_lag(0)
	, grass(0)
{
	
}

Game::~Game()
{
	delete m_pPlayer;
	m_pPlayer = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pInputHandler;
	m_pInputHandler = 0;

	for (unsigned int i = 0; i < grass.size(); ++i)
	{
		delete grass[i];
	}
	grass.clear();
}

bool 
Game::Initialise()
{
	const int width = 800;
	const int height = 600;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	// W02.1: Load the player ship sprite. DONE
	// For example: Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");
	Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\blackwidow1.png");
	// W02.1: Create the player ship instance. DONE
	m_pPlayer = new Player();
	m_pPlayer->Initialise(pPlayerSprite);
	ResetPlayer(width, height);

	
	SpawnGrass(width-50, height - 50);
	SpawnGrass(width - 100, height - 50);
	SpawnGrass(width - 150, height - 50);
	SpawnGrass(width - 200, height - 50);
	SpawnGrass(width - 250, height - 50);
	SpawnGrass(width - 50, height - 100);
	SpawnGrass(width - 100, height - 100);
	SpawnGrass(width - 150, height - 100);
	SpawnGrass(width - 200, height - 100);
	SpawnGrass(width - 50, height - 150);
	SpawnGrass(width - 100, height - 150);
	SpawnGrass(width - 150, height - 150);
	SpawnGrass(width - 50, height - 200);
	SpawnGrass(width - 100, height - 200);
	SpawnGrass(width - 50, height - 250);

	SpawnBounce(width - 250, height /2 );
	SpawnBounce(width - 100, 100);

	SpawnGrass(0, 50);
	SpawnExit(0, 0);

	SpawnGrass(0, height/2);
	SpawnEnter(0, (height / 2) - 50);

	//SpawnEnter()



	SpawnGrass(200, height - 50);
	SpawnDamage(0, height - 50);
	SpawnBounce(width / 2, height - 50);
	// W02.2: Spawn four rows of 14 alien enemies.

	// W02.2: Fill the container with these new enemies.

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	return (true);
}

void
Game::ResetPlayer(int width, int height)
{
	
	m_pPlayer->SetPositionX(width / 2);
	m_pPlayer->SetPositionY(height / 2);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);
	
	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}
		
		Draw(*m_pBackBuffer);
	}

	SDL_Delay(1);

	return (m_looping);
}

void 
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	for (unsigned int i = 0; i < grass.size(); ++i)
	{
		grass[i]->Process(deltaTime);
	}

	PlayerIsOnGround();

	// Update the game world simulation:

	// Ex003.5: Process each alien enemy in the container.

	// W02.3: Process each bullet in the container.

	// W02.1: Update player... DONE
	m_pPlayer->Process(deltaTime);
	
	

	// W02.3: Check for bullet vs alien enemy collisions...
	// W02.3: For each bullet
	// W02.3: For each alien enemy
	// W02.3: Check collision between two entities.
	// W02.3: If collided, destory both and spawn explosion.

	// W02.3: Remove any dead bullets from the container...

	// W02.3: Remove any dead enemy aliens from the container...

	// W02.3: Remove any dead explosions from the container...
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	for (unsigned int i = 0; i < grass.size(); ++i)
	{
		grass[i]->Draw(backBuffer);
	}

	// W02.2: Draw all enemy aliens in container...

	// W02.3: Draw all bullets in container...

	// W02.1: Draw the player ship...DONE
	m_pPlayer->Draw(backBuffer);

	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void
Game::MovePlayerLeft()
{
	// W02.1: Tell the player ship to move left. DONE
	m_pPlayer->SetHorizontalVelocity(-200);
}

// W02.1: Add the method to tell the player ship to move right... DONE
void
Game::MovePlayerRight()
{
	m_pPlayer->SetHorizontalVelocity(200);
}

void
Game::PlayerJump()
{
	/*if (!m_pPlayer->GetJumping())
	{
		m_pPlayer->Jump();
	}*/
	if (m_pPlayer->isOnGround)
		m_pPlayer->isOnGround = false;
		m_pPlayer->Jump();
}

void
Game::StopMovement()
{
	m_pPlayer->SetHorizontalVelocity(0);
}


// W02.3: Space a Bullet in game.
void 
Game::FireSpaceShipBullet()
{
	// W02.3: Load the player bullet sprite.      

	// W02.3: Create a new bullet object.

	// W02.3: Set the bullets vertical velocity.

	// W02.3: Add the new bullet to the bullet container.
}

// W02.2: Spawn a Enemy in game.
void 
Game::SpawnEnemy(int x, int y)
{
	// W02.2: Load the alien enemy sprite file.

	// W02.2: Create a new Enemy object. 

	// W02.2: Add the new Enemy to the enemy container.
}

void
Game::SpawnGrass(int x, int y)
{
	Sprite* grassSprite = m_pBackBuffer->CreateSprite("assets\\grass.png");
	Tile* tile = new Tile();
	tile->SetType(Tile::GRASS);
	tile->Initialise(grassSprite);
	tile->SetPositionX(x);
	tile->SetPositionY(y);
	grass.push_back(tile);
}

void
Game::SpawnDamage(int x, int y)
{
	Sprite* sprite = m_pBackBuffer->CreateSprite("assets\\damage.png");
	Tile* tile = new Tile();
	tile->SetType(Tile::DAMAGE);
	tile->Initialise(sprite);
	tile->SetPositionX(x);
	tile->SetPositionY(y);
	grass.push_back(tile);
}

void
Game::SpawnEnter(int x, int y)
{
	Sprite* sprite = m_pBackBuffer->CreateSprite("assets\\enter.png");
	Tile* tile = new Tile();
	tile->SetType(Tile::ENTER);
	tile->Initialise(sprite);
	tile->SetPositionX(x);
	tile->SetPositionY(y);
	grass.push_back(tile);
}

void
Game::SpawnExit(int x, int y)
{
	Sprite* sprite = m_pBackBuffer->CreateSprite("assets\\exit.png");
	Tile* tile = new Tile();
	tile->SetType(Tile::EXIT);
	tile->Initialise(sprite);
	tile->SetPositionX(x);
	tile->SetPositionY(y);
	grass.push_back(tile);
}

void
Game::SpawnBounce(int x, int y)
{
	Sprite* sprite = m_pBackBuffer->CreateSprite("assets\\bounce.png");
	Tile* tile = new Tile();
	tile->SetType(Tile::BOUNCE);
	tile->Initialise(sprite);
	tile->SetPositionX(x);
	tile->SetPositionY(y);
	grass.push_back(tile);
}

void
Game::PlayerIsOnGround()
{
	bool collide = false;

	SDL_Rect* playerRect = new SDL_Rect();

	playerRect->x = m_pPlayer->GetPositionX();
	playerRect->w = 33;
	playerRect->y = m_pPlayer->GetPositionY();
	playerRect->h = 50;

	for (unsigned int t = 0; t < grass.size() && collide == false; ++t)
	{
		SDL_Rect* tileRect = new SDL_Rect();
		tileRect->x = grass[t]->GetPositionX();
		tileRect->w = 50;
		tileRect->y = grass[t]->GetPositionY();
		tileRect->h = 50;

		SDL_Rect* fuckit = new SDL_Rect();

		if (SDL_IntersectRect(playerRect, tileRect, fuckit))
		{
			collide = true;
			switch (grass[t]->type)
			{
			case Tile::GRASS:
				if (playerRect->y + playerRect->h >= tileRect->y)
				{
					m_pPlayer->SetPositionY(tileRect->y - 50);
				}
				break;
			case Tile::BOUNCE:
				m_pPlayer->SetVerticalVelocity(-700);
				collide = false;
				break;
			case Tile::DAMAGE:
				ResetPlayer(800,600);
				break;
			case Tile::ENTER:
				m_pPlayer->SetPositionX(0);
				m_pPlayer->SetPositionY(0);
				break;
			case Tile::EXIT:
				collide = false;
				break;
			}
			//// Check if player is on top
			//if (playerRect->y + playerRect->h >= tileRect->y)
			//{
			//	m_pPlayer->SetPositionY(tileRect->y - 50);
			//}

			//else if (playerRect->x + playerRect->w <= tileRect->x)
			//{
			//	m_pPlayer->SetPositionX(tileRect->x - playerRect->w);
			//}

			//else if (playerRect->x >= tileRect->x + tileRect->w)
			//{
			//	m_pPlayer->SetPositionX(tileRect->x);
			//}
		}


		/*Cond1.If A's left edge is to the right of the B's right edge, -then A is Totally to right Of B
			Cond2.If A's right edge is to the left of the B's left edge, -then A is Totally to left Of B
			Cond3.If A's top edge is below B's bottom edge, -then A is Totally below B
			Cond4.If A's bottom edge is above B's top edge, -then A is Totally above B*/

		delete tileRect;
		tileRect = 0;
		delete fuckit;
		fuckit = 0;
	}

	delete playerRect;
	playerRect = 0;

	if (collide)
	{
		m_pPlayer->IsOnGround(true);
	}
	else
	{
		m_pPlayer->IsOnGround(false);
	}
}


