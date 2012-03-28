////////////////////////////////////////////////////////////////////////////////
// Filename: BitmapClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BITMAPCLASS_H_
#define _BITMAPCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <D3DX10.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TextureClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: BitmapClass
////////////////////////////////////////////////////////////////////////////////
class BitmapClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool Initialise(ID3D10Device*, int, int, WCHAR*, int, int);
	void Shutdown();
	bool Render(ID3D10Device*, int, int);

	int GetIndexCount();
	ID3D10ShaderResourceView* GetTexture();

private:
	bool InitialiseBuffers(ID3D10Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(int, int);
	void RenderBuffers(ID3D10Device*);

	bool LoadTexture(ID3D10Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D10Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
};

#endif