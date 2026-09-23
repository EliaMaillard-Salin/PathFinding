#include "Vector2.h"

#include <cmath>

bool Vector2::operator==(const Vector2& goal) const
{
	return x == goal.x && y == goal.y;
}

Vector2 Vector2::operator-(const Vector2& vector2) const
{
	return Vector2(x - vector2.x, y - vector2.y);
}

int Vector2::SqrDistance()
{
	return std::sqrt(std::pow(x,2) + std::pow(y,2));
}

std::string Vector2::ToString()
{
	std::string re = "{ X : " + std::to_string(x) + ", Y : " + std::to_string(y) + " }";
	return re;
}