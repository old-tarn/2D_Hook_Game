#include "player.h"
#include "sprite.h"

Player::Player() :
gravity(42)
, isOnGround(0)
, currentCollisions(0)
{

}

Player::~Player()
{
	// DOES NOT NEED TO DELETE CURRENT COLLISIONS GAME::~GAME() DOES THIS
}

void
Player::Process(float deltaTime)
{
	// Processes gravity
	if (isOnGround)
	{
		m_velocityY = 0;
	}
	else{ 
		m_velocityY += gravity;
		if (m_velocityY <= 0) /* Once player has reached the peak of the jump */
		{
			m_isJumping = false;
		}
	}
	

	// Stops player falling throught the bottom of the screen. Might disable this and replace with death notice. 
	if (m_y > 600 - m_pSprite->GetHeight())
	{
		m_y = 600 - m_pSprite->GetHeight();
		isOnGround = true;
	}

	Entity::Process(deltaTime);
}

void
Player::Jump()
{
	if (!m_isJumping)
	{
		m_velocityY = -800;
		m_isJumping = true;
	}
	// TODO: MAX HEIGHT OF JUMP = 2.5 UNIT ~ 125px;
	// TODO: MAX DISTANCE = 4 UNIT ~ 200 px;
	// TODO: NEED TO WORK ON JUMP TIMING -- Possibly 0.44seconds to reacn 2.5 units high
}

void
Player::IsOnGround(bool value)
{
	isOnGround = value;
}
