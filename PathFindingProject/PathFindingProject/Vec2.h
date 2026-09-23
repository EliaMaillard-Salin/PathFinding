#pragma once

#include <string>

struct Vec2
{
	float x, y;
	Vec2(float _x = 0, float _y = 0) :x(_x), y(_y) {}
	bool operator==(const Vec2& goal) const;
	Vec2 operator-(const Vec2& vector2) const;
	float SqrDistance();  //using - operator
	std::string ToString();
};

