#include "Vec2.h"

#include <cmath>

bool Vec2::operator==(const Vec2& goal) const
{
	return x == goal.x && y == goal.y;
}

Vec2 Vec2::operator-(const Vec2& vector2) const
{
	return Vec2(x - vector2.x, y - vector2.y);
}

float Vec2::SqrDistance()
{
	return std::sqrt(std::pow(x,2) + std::pow(y,2));
}

std::string Vec2::ToString()
{
	std::string re = "{ X : " + std::to_string(x) + ", Y : " + std::to_string(y) + " }";
	return re;
}