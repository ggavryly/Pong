#pragma once
#include "Vector.hpp"
#include "SDL2_API.hpp"
#include "main.hpp"
#include "Player.hpp"
#include "Ball.hpp"

class Game : public SDL2_API
{
public:
	Game();
	~Game();
	void	play();
private:
	ESide	gameLoop();
	ESide	gameTick();
	void	botMove();
	void	win(ESide);
private:
	Texture		*background;
	Player		left;
	Player		right;
	Ball		ball;
	Uint32		win_score = 3;
	EDifficulty	difficulty;
	
};


