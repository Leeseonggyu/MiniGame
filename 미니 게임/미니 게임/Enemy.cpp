#include "Enemy.h"
#include "InputHandler.h"
#include "Vector2D.h"


Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_velocity.setY(2);
	m_velocity.setX(1);
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
	if (m_position.getY() < 0) {
		m_velocity.setX(-2);
		m_velocity.setY(2);
	}
	else if (m_position.getX() < 0)
	{
		m_velocity.setX(2);
		m_velocity.setY(2);
	}
	else if (m_position.getY() > 380) {
		m_velocity.setX(2);
		m_velocity.setY(-2);
	}
	else if (m_position.getX() > 840) {
		m_velocity.setX(-2);
		m_velocity.setY(-2);
	}
	SDLGameObject::update();
}

void Enemy::handleInput()
{
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(1);
	}

	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_velocity = (*vec - m_position) / 100.0f;
}
void Enemy::clean()
{
}