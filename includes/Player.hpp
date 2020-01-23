#pragma once
#include "GameEntity.hpp"
#include "SDL2_API.hpp"

enum EDifficulty
{
	EASY = 2,
	MEDIUM = 4,
	HARD = 8,
	NONBOT = -1
};

enum ESide
{
	ERIGHT,
	ELEFT
};

extern SDL_Rect viewport;

class Player : public GameEntity
{
public:

	void	movement(ObjectMove, EDifficulty dif);
	void	init(ESide);
	void	scorePoint();
	void	drawScore(ESide);
	Uint32	getScore() const;
	void	checkEdge();

private:
	Uint32		score;
};


