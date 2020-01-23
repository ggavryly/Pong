#include "Player.hpp"

void Player::init(ESide side)
{
	score = 0;
	size.x = viewport.w / 35.0;
	size.y = viewport.h / 4;
	switch (side)
	{
		case ELEFT:
			pos.x = 10;
			pos.y = viewport.h / 2 - size.y / 2;
			break;
		case ERIGHT:
			pos.x = (viewport.w - size.x) - 10;
			pos.y = viewport.h / 2 - size.y / 2;
			break;
	}
}

void Player::checkEdge()
{
	if (pos.y < 5)
		pos.y = 10;
	if (pos.y + size.y + 5 > viewport.h)
		pos.y -= 10;
}

void Player::scorePoint()
{
	score += 1;
}

void Player::movement(ObjectMove move, EDifficulty dif)
{
	switch (move)
	{
		case UP:
		{
			pos.y -= (dif == NONBOT) ? (10) : (static_cast<float>(dif) / 10);
			break;
		}
		case DOWN:
		{
			pos.y += (dif == NONBOT) ? (10) : (static_cast<float>(dif) / 10);
			break;
		}
	}
	checkEdge();
}

Uint32 Player::getScore() const
{
	return score;
}
