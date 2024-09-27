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
		return Vector2(x, y);
	}

	Vector2 operator+(Vector2 other)
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(Vector2 other)
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator/(float other)
	{
		return Vector2(x / other, y / other);
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2 Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;

		return *this;
	}


};
