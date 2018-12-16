#pragma once
#include"GameState.h"

class MenuState : public GameState
{
private:
	static MenuState* s_pInstance;
	MenuState() {};
	static void s_menuToPlay();
	static void s_exitFromMenu();
	static const std::string s_menuID;
public:
	~MenuState() {};

	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_menuID; }
	SDL_Texture*m_pTexture;
	static MenuState* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new MenuState();
			return s_pInstance;
		}
		return s_pInstance;
	}
};
typedef MenuState TheMenuState;