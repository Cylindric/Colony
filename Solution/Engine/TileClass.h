#ifndef _TILECLASS_H_
#define _TILECLASS_H_

#include "main.h"
class TextureClass;

static const int TILE_SIZE = 32;


enum TileType
{
	TILE_TYPE_OPEN = 1,
	TILE_TYPE_WALL = 2
};

enum TileTextureId
{
	TILE_TEX_WALLS = 16,
	TILE_TEX_HIGHLIGHT = 32
};

enum TileTextureType
{
	TILE_TEXTYPE_TEE,
	TILE_TEXTYPE_CORNER,
	TILE_TEXTYPE_END,
	TILE_TEXTYPE_CROSS,
	TILE_TEXTYPE_STRAIGHT
};

enum Directions
{
	DIRECTION_N = 1,
	DIRECTION_E = 2,
	DIRECTION_S = 4,
	DIRECTION_W = 8
};


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

	bool Initialize(ID3D10Device* device, TextureClass* texture);
	void Shutdown();
	bool Render(ID3D10Device* device, int screenWidth, int screenHeight);
	int GetTypeId();
	void SetTypeId(int);
	void SetTextureId(int);
	void SetPosition(int x, int y);

	int GetIndexCount();
	ID3D10ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D10Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(int, int);
	void RenderBuffers(ID3D10Device*);

private:
	ID3D10Buffer *m_VertexBuffer, *m_IndexBuffer;
	int m_VertexCount, m_IndexCount;
	TextureClass* m_Texture;
	int m_ScreenWidth, m_ScreenHeight;
	int m_PreviousPosX, m_PreviousPosY;
	int m_TypeId; // the primary type of the tile
	int m_TextureId; // the texture tile id
	int m_PosX;
	int m_PosY;
};

#endif