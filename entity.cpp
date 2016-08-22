// COMP710 GP 2D Framework

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>

Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
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
	m_x += m_velocityX * deltaTime;
	m_y += m_velocityY * deltaTime;

	if (m_x <= 0)
	{
		m_x = 0;
	}
	else if (m_x >= (800 - m_pSprite->GetWidth()))
	{
		m_x = 800 - m_pSprite->GetWidth();
	}

	/*if (m_y > 600 - m_pSprite->GetHeight())
	{
		m_y = 600 - m_pSprite->GetHeight();
	}
	else if (m_y <= 0)
	{
		m_y = 0;
		m_velocityY = 0;
	}*/

	if (m_y <= 0)
	{
		m_y = 0;
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

bool
Entity::IsCollidingWith(Entity& e)
{
	// W02.3: Generic Entity Collision routine.

	// W02.3: Does this object collide with the e object?
	// W02.3: Create a circle for each entity (this and e).

	// W02.3: Check for intersection.
	// W02.3: Using circle-vs-circle collision detection.

	// W02.3: Return result of collision.

	return (false); // W02.4 Change return value!
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