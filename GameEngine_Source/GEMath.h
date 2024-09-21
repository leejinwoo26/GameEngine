#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{
	}
	Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{
	}

	Vector2 operator=(Vector2 pos)
	{
		x = pos.x;
		y = pos.y;
	}
};
