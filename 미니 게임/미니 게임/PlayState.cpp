#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"
#include "SDLGameObject.h"
#include "GameOverState.h"
#include <SDL.h>

const std::string PlayState::s_playID = "PLAY";
PlayState* PlayState::s_pInstance = NULL;

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	return true;
}

void PlayState::update()
{

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
	if (checkCollision(
		dynamic_cast<SDLGameObject*>(m_gameObjects[1]),
		dynamic_cast<SDLGameObject*>(m_gameObjects[2])))
	{
		TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(PauseState::Instance());
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	//SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 0, 0, 255);
	if (!TheTextureManager::Instance()->load("assets/battleback.png",
		"back", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/Castlemaze_Reimu.png",
		"Reimu", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Castlemaze_Enemies.png",
		"Enemy", TheGame::Instance()->getRenderer())) {
		return false;
	};
	GameObject* background = new Background(new LoaderParams(0, 0, 853, 480, "back"));
	
	GameObject* player = new Player(
		new LoaderParams(500, 100, 76, 82, "Reimu"));
	GameObject* enemy = new Enemy(
		new LoaderParams(100, 100, 92, 122, "Enemy"));

	//배경 이미지 출력 실패 게임 오브젝트로 출력시 충돌로 게임 오버 일어남
	m_gameObjects.push_back(background);
	m_gameObjects.push_back(player);
	m_gameObjects.push_back(enemy);
	
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	};
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("helicopter");
	std::cout << "exiting PlayState\n";
	return true;
}

void SDLGameObject::draw()
{
	if (m_velocity.getX() > 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer(),
			SDL_FLIP_HORIZONTAL);
	}
	else {
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer());
	}
}