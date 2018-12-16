#include "MenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include <SDL_image.h>
#include "Background.h"

const std::string MenuState::s_menuID = "MENU";
MenuState* MenuState::s_pInstance = 0;

void MenuState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MenuState::render()
{

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter()
{
    //SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 0, 0, 255);
	if (!TheTextureManager::Instance()->load("assets/grid_bg.png",
		"back", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
    if (!TheTextureManager::Instance()->load("assets/button.png",
        "playbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("assets/exit.png",
        "exitbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
	GameObject* background = new Background(
		new LoaderParams(25, 0, 800, 600, "back"));

    GameObject* button1 = new MenuButton(
        new LoaderParams(240, 100, 400, 100, "playbutton"),
        s_menuToPlay);

    GameObject* button2 = new MenuButton(
        new LoaderParams(240, 300, 400, 100, "exitbutton"),
        s_exitFromMenu);
	

	m_gameObjects.push_back(background);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit()
{
    //SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()
        ->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()
        ->clearFromTextureMap("exitbutton");
    std::cout << "exiting MenuState\n";
    return true;
}

void MenuState::s_menuToPlay()
{

    TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
}

void MenuState::s_exitFromMenu()
{
    TheGame::Instance()->quit();
}