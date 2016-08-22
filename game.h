// COMP710 GP 2D Framework
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Player;
class Tile;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

	void MovePlayerLeft();
	void MovePlayerRight();
	void PlayerJump();
	void StopMovement();

	void FireSpaceShipBullet();

	void SpawnEnemy(int x, int y);
	void SpawnExplosion(int x, int y);
	
	void SpawnGrass(int x, int y);
	void SpawnBounce(int x, int y);
	void SpawnDamage(int x, int y);
	void SpawnEnter(int x, int y);
	void SpawnExit(int x, int y);

	void ResetPlayer(int width, int height);

	void PlayerIsOnGround();
	
protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Game Entities:
	// W02.1: Add a PlayerShip field.     DONE
	Player* m_pPlayer;
	std::vector<Tile*> grass;

	// W02.2: Add an alien enemy container field.
	// W02.3: Add a bullet container field.

private:

};

#endif // __GAME_H__
