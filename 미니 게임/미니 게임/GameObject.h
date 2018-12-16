#pragma once
#include "SDL.h"
#include <map>
#include "LoaderParams.h"

class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

protected:
	GameObject(const LoaderParams* pParams) {}
	virtual ~GameObject() {}
	std::string m_textureID;
	int m_currentFrame;
	int m_currentRow;
	int m_x;
};