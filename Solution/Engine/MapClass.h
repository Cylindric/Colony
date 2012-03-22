#ifndef _MAPCLASS_H_
#define _MAPCLASS_H_

#include "main.h"
class TextureShaderClass;
class TextureClass;
class TileClass;


class MapClass
{
public:
	MapClass(void);
	~MapClass(void);
	bool Initialise(ID3D10Device*, int, int);
	bool Render(ID3D10Device*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, TextureShaderClass*);
	void Shutdown();

private:
	TextureClass* m_Texture;
	std::vector<TileClass*> m_Tiles;
};

#endif