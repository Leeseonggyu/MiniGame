#include "Player.h"
#include "InputHandler.h"
#include "Game.h"
#include "PlayState.h"

Uint32 startTime, currentTime;
const float shootTime = 400.0f;

Player::Player(const LoaderParams* pParams) :SDLGameObject(pParams)
{
}

void Player::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
	handleInput(); // add our function
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
	SDLGameObject::update();

}

void Player::clean()
{
}
void Player::fire()
{
	
}
void Player::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(2);
	}

	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(1);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		startTime = SDL_GetTicks();

		if (shootTime <= startTime - currentTime)
		{
			Bullet *bullet = new Bullet(new LoaderParams(Player::m_position.getX() + 128, Player::m_position.getY() + 10, 47, 47, "bullet"));
			PlayState::Instance()->m_bullet.push_back(bullet);
			currentTime = SDL_GetTicks();
		}
	}
	// void Enemy::handleInput() 추가 : 마우스 motion
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_velocity = (*vec - m_position) / 100;

	Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	m_velocity = *target - m_position;
	m_velocity /= 50;
}