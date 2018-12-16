#pragma once
#include "GameState.h"
#include "SDLGameObject.h"
#include "Background.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	virtual std::string getStateID() const { return s_playID; }

	static PlayState* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new PlayState();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Rect m_sourceRectangle;
private:
	static const std::string s_playID;
	static PlayState* s_pInstance;
	std::vector<GameObject*> m_gameObjects;
	Background* m_back;
};
typedef PlayState ThePlayState;