#include "Background.h"
#include "InputHandler.h"
#include"TextureManager.h"
#include"Game.h"
#include<SDL.h>


Background::Background(const LoaderParams* pbacks)
	: SDLGameObject(pbacks)
{
	BackX = pbacks->getX();
}
void Background::draw()
{
	//SDLGameObject::draw(); // we now use SDLGameObject
	TextureManager::Instance()->draw(m_textureID,
		(int)m_position.getX(), (int)m_position.getY(),
		m_width, m_height, TheGame::Instance()->getRenderer());
}
void Background::update()
{
}
void Background::clean()
{
}