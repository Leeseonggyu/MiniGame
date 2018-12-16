#include "Bullet.h"
#include "InputHandler.h"
#include "Vector2D.h"
#include "Player.h"

Bullet::Bullet(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_velocity.setX(2);
}

void Bullet::draw()
{
	SDLGameObject::draw();
}

void Bullet::update()
{
	m_position += m_velocity;
}

void Bullet::clean()
{
	TheTextureManager::Instance()->clearFromTextureMap("bullet");
}
void Bullet::Frame(int change)
{
	this->m_currentFrame = change;
}