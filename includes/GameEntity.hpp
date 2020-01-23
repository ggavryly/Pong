#pragma once
#include "main.hpp"
#include "Vector.hpp"
#include "SDL2_API.hpp"

enum ObjectMove
{
	RIGHT,
	LEFT,
	DOWN,
	UP,
	NOTHING
};

class GameEntity
{
public:
	virtual void	checkEdge() = 0;
	bool			collision(GameEntity const &obj) const
	{
		if (pos.x < obj.pos.x + obj.size.x &&
			pos.x + size.x > obj.pos.x &&
			pos.y < obj.pos.y + obj.size.y &&
			pos.y + size.y > obj.pos.y)
		{
			return true;
		}
		return false;
	}
	void	loadTexture(Texture *texture)
	{
		GameEntity::texture = texture;
	}
	
	Texture *getTexture() const
	{
		return texture;
	}
	
	const Vector &getPos() const
	{
		return pos;
	}
	
	const Vector &getDir() const
	{
		return dir;
	}
	
	const Vector &getSize() const
	{
		return size;
	}
	
	float getVelocity() const
	{
		return velocity;
	}

protected:
	Texture		*texture;
	Vector		pos;
	Vector		dir;
	Vector		size;
	float		velocity;
};

