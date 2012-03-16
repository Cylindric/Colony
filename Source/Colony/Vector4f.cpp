#include "Vector4f.h"


Vector4f& Vector4f::operator+=(const Vector4f &rhs)
{
	x += rhs.x;
	y += rhs.y;
	u += rhs.u;
	v += rhs.v;
	return *this;
}


const Vector4f Vector4f::operator+(const Vector4f &rhs)
{
	Vector4f v = *this;
	v += rhs;
	return v;
}


const Vector4f Vector4f::operator*(const float &rhs)
{
	Vector4f v = *this;
	v.x *= rhs;
	v.y *= rhs;
	v.u *= rhs;
	v.v *= rhs;
	return v;
}
