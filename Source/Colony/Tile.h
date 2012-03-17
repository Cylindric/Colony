#ifndef _CTILE_H_
#define _CTILE_H_

#include <GL/glew.h>

class CTile
{
public:
	CTile(void);
	CTile(int x, int y, int typeId, int texId);
	~CTile(void);
	void onRender(GLuint texture);
	void setPosition(int x, int y);
	void setTextureId(int id);
	void setTypeId(int id);

private:
	int typeId;
	int	textureId;
	int posX;
	int posY;

};

#endif