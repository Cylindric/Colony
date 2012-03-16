#ifndef _CVECTOR4F_H_
#define _CVECTOR4F_H_

#include <GL/glew.h>

class Vector4f
{
public:
	GLfloat x;
	GLfloat y;
	GLfloat u;
	GLfloat v;
	const Vector4f operator+(const Vector4f &rhs);
	const Vector4f operator*(const float &rhs);
	Vector4f& operator+=(const Vector4f &rhs);
};

#endif