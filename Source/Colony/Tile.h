#ifndef _CTILE_H_
#define _CTILE_H_

#include <GL/glew.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class CTile
{
public:
	CTile(void);
	CTile(int x, int y, int texId);
	~CTile(void);
	void onRender(GLuint texture);
	void setPosition(int x, int y);
	void setTextureId(int id);

private:
	int	textureId;
	int posX;
	int posY;

};

#endif