// COMP710 GP 2D Framework

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>
#include <cmath>

Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
, m_canMoveLeft(1)
, m_canMoveRight(1)
, m_isJumping(0)
{

}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

void 
Entity::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

	// W02.1: Generic position update, based upon velocity (and time). DONE
	if (m_canMoveLeft && m_velocityX < 0)
	{
		m_x += m_velocityX * deltaTime;
	}
	else if (m_canMoveRight && m_velocityX > 0)
	{
		m_x += m_velocityX * deltaTime;
	}
	else
	{
		m_velocityX = 0;
	}
	
	if (!m_isJumping)
	m_y += m_velocityY * deltaTime;
	

	if (m_x <= 0)
	{
		m_x = 0;
	}
	else if (m_x >= (800 - m_pSprite->GetWidth()))
	{
		m_x = 800 - (float)m_pSprite->GetWidth();
	}

	if (m_y <= 0)
	{
		m_y = 0;
		m_velocityY = 0;
	}
	else if (m_y >= 600)
	{
		m_y = 600;
		m_velocityY = 0;
	}

	// W02.1: Boundary checking and position capping. DONE
}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}

Entity::Collision
Entity::IsCollidingWith(Entity& e)
{
	//  Minkowski sum
	float w = 0.5 * (m_pSprite->GetWidth() + e.m_pSprite->GetWidth()); // Width of both
	float h = 0.5 * (m_pSprite->GetHeight() + e.m_pSprite->GetHeight()); // Height of both
	float dx = (m_x + m_pSprite->GetWidth()*0.5) - (e.m_x + e.m_pSprite->GetWidth()*0.5); // Center A.x - Center B.x
	float dy = (m_y + m_pSprite->GetHeight()*0.5) - (e.m_y + e.m_pSprite->GetHeight()*0.5); // Center A.y - Center B.y

	if (abs(dx) <= w && abs(dy) <= h)
	{
		/* collision! */
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				/* collision at the top */
				return TOP;
			}
			else
			{
				/* on the left */
				return LEFT;
			}
		}
		else
		{
			if (wy > -hx)
			{
				/* on the right */
				return RIGHT;
			}
			else
			{
				/* at the bottom */
				return BOTTOM;
			}
		}
	}

	// W02.3: Generic Entity Collision routine.	

	return NONE; // W02.4 Change return value!
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

float 
Entity::GetPositionX()
{
	return (m_x);
}

float 
Entity::GetPositionY()
{
	return (m_y);
}

float 
Entity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity()
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}