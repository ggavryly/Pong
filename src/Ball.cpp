#include "Ball.hpp"

Ball::Ball()
{}

void Ball::movement(ObjectMove)
{
	pos.x += dir.x;
	pos.y += dir.y;
	checkEdge();
}

void Ball::wrapX()
{
	dir.x = -dir.x;
}

void Ball::wrapY()
{
	dir.y = -dir.y;
}

void Ball::init()
{
	static int i = 1;
	srand(time(nullptr));
	goal = 0;
	size.x = 50;
	size.y = size.x;
	pos.x = viewport.w / 2 - size.x / 2;
	pos.y = viewport.h / 2 - size.y / 2;
	dir = Vector((rand() + i) % 360,0,0).normalization();
}

void Ball::checkEdge()
{
	if (pos.x < 0)
	{
		goal = 1;
	}
	if (pos.x + size.x >= viewport.w)
	{
		goal = 2;
	}
	if (pos.y < 0 || pos.y + size.y / 2 >= viewport.h)
		wrapY();
}