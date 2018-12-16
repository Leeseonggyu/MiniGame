#pragma once
#include"GameObject.h"
#include"GameState.h"

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_gameOverID; }

    static GameOverState* Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new GameOverState();
            return s_pInstance;
        }
        return s_pInstance;
    }
private:
	static void s_gameOverToMain();
	static void s_restartPlay();
    static GameOverState* s_pInstance;
	static const std::string s_gameOverID;
	std::vector<GameObject*> m_gameObjects;
};
typedef GameOverState TheGameOverState;