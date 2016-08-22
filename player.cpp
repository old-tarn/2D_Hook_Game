#include "player.h"
#include "sprite.h"

Player::Player() :
  gravity(10)
, isOnGround(0)
{

}

Player::~Player()
{
	
}

void
Player::Process(float deltaTime)
{
	if (isOnGround)
	{
		m_velocityY = 0;
	}
	else{
		m_velocityY += gravity;
	}
	
	if (m_y > 600 - m_pSprite->GetHeight())
	{
		m_y = 600 - m_pSprite->GetHeight();
		isOnGround = true;
	}
	/*else
	{
		isOnGround = false;
		canJump = false;
	}*/

	

	//if (jumping)
	//{
	//	
	//	/*if (m_y > 600 - m_pSprite->GetHeight())
	//	{
	//		m_velocityY = 0;
	//		jumping = false;
	//	}*/
	//}

	Entity::Process(deltaTime);
}

void
Player::Jump()
{
	m_velocityY = -300;
}

void
Player::IsOnGround(bool value)
{
	isOnGround = value;
}
