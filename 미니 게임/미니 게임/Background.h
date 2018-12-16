#pragma once
#include "SDLGameObject.h"

class Background : public SDLGameObject
{
private:
	float BackX;
	//	void handleInput();
public:
	Background(const LoaderParams* pbacks);
	virtual void draw();
	virtual void update();
	virtual void clean();
};