#include "entity.h"
#include <vector>

class Player : public Entity
{
public:
	Player();
	~Player();

	void Process(float deltaTime);
	void Jump();
	
	void IsOnGround(bool value);

	// Member Data

	std::vector<Entity*> currentCollisions;
	bool isOnGround;
	const int gravity;
	
};