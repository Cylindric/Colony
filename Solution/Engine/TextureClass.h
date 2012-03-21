#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_

#include <D3D10.h>
#include <D3DX10.h>

class TextureClass
{

public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialise(ID3D10Device*, WCHAR*);
	void Shutdown();
	ID3D10ShaderResourceView* GetTexture();

private:
	ID3D10ShaderResourceView* m_Texture;

};

#endif