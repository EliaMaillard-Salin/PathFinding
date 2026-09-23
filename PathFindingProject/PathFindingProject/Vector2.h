#pragma once

#include <string>

struct Vector2
{
	int x, y;
	Vector2(int _x = 0, int _y = 0) :x(_x), y(_y) {}
	bool operator==(const Vector2& goal) const;
	Vector2 operator-(const Vector2& vector2) const;
	int SqrDistance();  //using - operator
	std::string ToString();
};

