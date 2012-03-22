#ifndef _TILECLASS_H_
#define _TILECLASS_H_

#include "main.h"
class TextureClass;

static const int TILE_SIZE = 32;

class TileClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
	};

public:
	TileClass();
	TileClass(const TileClass&);
	~TileClass();

	bool Initialize(ID3D10Device* device, int screenWidth, int screenHeight, TextureClass* texture);
	void Shutdown();
	bool Render(ID3D10Device*);
	void SetId(int);
	void SetPosition(int x, int y);

	int GetIndexCount();
	ID3D10ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D10Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(int, int);
	void RenderBuffers(ID3D10Device*);

private:
	ID3D10Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	int m_screenWidth, m_screenHeight;
	int m_previousPosX, m_previousPosY;
	int m_id;
	int m_posX;
	int m_posY;
};

#endif