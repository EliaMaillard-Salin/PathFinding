#pragma once

#include <string>

struct Vector2
{
	float x, y;
	Vector2(float _x = 0, float _y = 0) :x(_x), y(_y) {}
	bool operator==(const Vector2& goal) const;
	Vector2 operator-(const Vector2& vector2) const;
	float SqrDistance();  //using - operator
	std::string ToString();
};

