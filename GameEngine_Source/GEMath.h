#pragma once
#include <cmath>
#include "CommonInclude.h"
#define PI 3.141592f



struct Vector2
{
	float x;
	float y;

	static Vector2 One;
	static Vector2 Zero;
	static Vector2 Right;
	static Vector2 Left;
	static Vector2 Up;
	static Vector2 Down;


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


	static Vector2 ExponentialLerp(const Vector2& current,
		const Vector2& target, float t, float lambda)
	{
		return current + (target - current) * (1.0f - expf(-lambda * t));
	}

	static Vector2 SpringLerp(Vector2& position, Vector2& velocity,
		const Vector2& target, float damping, float stiffness, float deltaTime) {
		Vector2 force = (target - position) * stiffness;  // 목표 위치로의 힘
		Vector2 dampingForce = velocity * damping;        // 감쇠
		Vector2 acceleration = force - dampingForce;      // 가속도 계산

		velocity = velocity + acceleration * deltaTime;   // 속도 갱신
		position = position + velocity * deltaTime;       // 위치 갱신
		return position;
	}




	static Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.f) * PI;
		vector.normalize();
		float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
		float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

		return Vector2(x, y);
	}

	static float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	static float Cross(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}
	bool operator==(Vector2 v)
	{
		return (x == v.x) && (y == v.y);
	}
	Vector2 operator+(Vector2 other)
	{
		return Vector2(x + other.x, y + other.y);
	}


	void operator+=(Vector2 other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(Vector2 other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=(Vector2 other)
	{
		x *= other.x;
		y *= other.y;
	}

	void operator*=(float other)
	{
		x *= other;
		y *= other;
	}

	Vector2 operator-(Vector2 other)
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 operator/(float value)
	{
		return Vector2(x / value, y / value);
	}

	Vector2 operator*(float value)
	{
		return Vector2(x * value, y * value);
	}

	Vector2 operator*(Vector2 v)
	{
		return Vector2(x * v.x, y * v.y);
	}

	Vector2 operator=(Vector2 v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	Vector2 operator+(const Vector2& other) const {
		return { x + other.x, y + other.y };
	}

	// 벡터 간 뺄셈
	Vector2 operator-(const Vector2& other) const {
		return { x - other.x, y - other.y };
	}



	void clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2 normalize()
	{
		float len = length();
		x /= len;
		y /= len;

		return *this;
	}


	
};
