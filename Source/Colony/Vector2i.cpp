#include "Vector2i.h"


Vector2i& Vector2i::operator+=(const Vector2i &rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}


const Vector2i Vector2i::operator+(const Vector2i &rhs)
{
	Vector2i v = *this;
	v += rhs;
	return v;
}
