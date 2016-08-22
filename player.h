#include "entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Process(float deltaTime);
	void Jump();
	
	void IsOnGround(bool value);

	bool GetJumping();

	// Member Data


	bool isOnGround;
	const int gravity;
	
};