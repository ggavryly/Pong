#include "Game.hpp"

SDL_Rect viewport;
bool GKeys[(int)FRKey::COUNT] = {};

Game::Game()
{
	difficulty = MEDIUM;
	SDL_RenderGetViewport(renderer, &viewport);
	left.init(ELEFT);
	right.init(ERIGHT);
	ball.init();
	left.loadTexture(createTexture("textures/rocket.png"));
	right.loadTexture(createTexture("textures/rocket.png"));
	ball.loadTexture(createTexture("textures/ball.png"));
	background = createTexture("textures/background.png");
}

void Game::play()
{
	win(gameLoop());
}

void Game::win(ESide side)
{
	switch (side)
	{
		case ERIGHT:
		{
			std::cout << "Right player win" << std::endl;
		}
		case ELEFT:
		{
			std::cout << "Left player win" << std::endl;
		}
	}
	exit(0);
}

void Game::botMove()
{
	if (ball.getPos().y < right.getPos().y)
		right.movement(UP, difficulty);
	if (ball.getPos().y > right.getPos().y)
		right.movement(DOWN, difficulty);
}

Game::~Game()
{
	destroyTexture(left.getTexture());
	destroyTexture(right.getTexture());
	destroyTexture(ball.getTexture());
	destroyTexture(background);
}

ESide Game::gameTick()
{
	ball.movement(NOTHING);
	botMove();
	if (left.collision(ball) || right.collision(ball))
		ball.wrapX();
	if (ball.goal)
	{
		ball.goal == 1 ? right.scorePoint() : left.scorePoint();
		ball.init();
	}
	if (left.getScore() == win_score || left.getScore() == win_score)
	{
		return left.getScore() == win_score ? ELEFT : ERIGHT;
	}
	drawTexture(left.getTexture(), left.getPos().x, left.getPos().y, left.getSize().x, left.getSize().y);
	drawTexture(right.getTexture(), right.getPos().x, right.getPos().y, right.getSize().x, right.getSize().y);
	drawTexture(ball.getTexture(), ball.getPos().x, ball.getPos().y, ball.getSize().x, ball.getSize().y);
	drawText(std::to_string(left.getScore()), viewport.w / 4 , viewport.h / 4, 50, 100, (SDL_Color){.r = 0xFF, .g = 0xFF, .b = 0xFF});
	drawText(std::to_string(right.getScore()), viewport.w - viewport.w / 4 , viewport.h / 4, 50, 100, (SDL_Color){.r = 0xFF, .g = 0xFF, .b = 0xFF});
	return ESide(0);
}

ESide Game::gameLoop()
{
	int done = 0;
	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
						case SDLK_RIGHT:
						case SDLK_LEFT:
						case SDLK_DOWN:
						case SDLK_UP:
						{
							int key_index = (event.key.keysym.sym - SDLK_RIGHT);
							SDL2_API::onKeyReleased((FRKey)key_index);
							GKeys[key_index] = false;
							break;
						}
						case SDLK_ESCAPE:
							done = true;
							break;
						default:
							break;
					}
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_RIGHT:
						case SDLK_LEFT:
						case SDLK_DOWN:
						case SDLK_UP:
						{
							int key_index = (event.key.keysym.sym - SDLK_RIGHT);
							left.movement(ObjectMove(key_index), NONBOT);
							GKeys[key_index] = true;
						}
							break;
						case SDLK_r:
						{
							ball.init();
						}
						default:
							break;
						
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button <= SDL_BUTTON_RIGHT)
					{
						 SDL2_API::onMouseButtonClick((FRMouseButton)(event.button.button - SDL_BUTTON_LEFT), false);
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button <= SDL_BUTTON_RIGHT)
					{
						 SDL2_API::onMouseButtonClick((FRMouseButton)(event.button.button - SDL_BUTTON_LEFT), true);
					}
					break;
				case SDL_MOUSEMOTION:
					 SDL2_API::onMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
					break;
				case SDL_QUIT:
					done = true;
					break;
				default:
					break;
			}
		}
		if (old_time + fps > SDL_GetTicks())
			continue;
		else
		{
			old_time = SDL_GetTicks();
			
			SDL_RenderClear(renderer);
			
			SDL_RenderGetViewport(renderer, &viewport);
			
			/* Draw a background */
			drawTexture(background,0,0, viewport.w, viewport.h);
			
			done |= gameTick();
			SDL_RenderPresent(renderer);
		}
	}
	return ESide(done);
}
