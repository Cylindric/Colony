#ifndef _CVECTOR2I_H_
#define _CVECTOR2I_H_

#include <GL/glew.h>

class Vector2i
{
public:
	Vector2i(void);
	Vector2i(int x, int y);
	GLint x;
	GLint y;
	bool operator==(const Vector2i &rhs);
	const Vector2i operator+(const Vector2i &rhs);
	const Vector2i operator*(const float &rhs);
	Vector2i& operator+=(const Vector2i &rhs);
};

#endif