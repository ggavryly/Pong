#pragma once
#include "GameEntity.hpp"
#include "SDL2_API.hpp"

extern SDL_Rect viewport;

class Ball : public GameEntity
{
public:
	Ball();
	
	void	movement(ObjectMove);
	void	init();
	void 	wrapX();
	void 	wrapY();
	void	checkEdge();

public:
	int goal = 0;
};


