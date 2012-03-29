////////////////////////////////////////////////////////////////////////////////
// Filename: TileClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TILECLASS_H_
#define _TILECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <D3DX10.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TextureClass.h"


/////////////
// GLOBALS //
/////////////
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

enum TileTexId
{
	TILE_TEX_GROUND = 0,
	TILE_TEX_WALL_E = 16,
	TILE_TEX_WALL_S = 17,
	TILE_TEX_WALL_N = 18,
	TILE_TEX_WALL_W = 19,
	TILE_TEX_WALL_ES = 20,
	TILE_TEX_WALL_SW = 21,
	TILE_TEX_WALL_NE = 22,
	TILE_TEX_WALL_NW = 23,
	TILE_TEX_WALL_NES = 24,
	TILE_TEX_WALL_ESW = 25,
	TILE_TEX_WALL_NEW = 26,
	TILE_TEX_WALL_NSW = 27,
	TILE_TEX_WALL_NS = 28,
	TILE_TEX_WALL_EW = 29,
	TILE_TEX_WALL_NESW = 30,
	TILE_TEX_WALL_POST = 31
};

enum Directions
{
	DIRECTION_N = 1,
	DIRECTION_E = 2,
	DIRECTION_S = 4,
	DIRECTION_W = 8
};


////////////////////////////////////////////////////////////////////////////////
// Class name: TileClass
////////////////////////////////////////////////////////////////////////////////
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

	// Methods
	bool Initialise(ID3D10Device* device, TextureClass* texture);
	void Shutdown();
	bool Render(ID3D10Device* device, unsigned int screenWidth, unsigned int screenHeight);

	// Properties
	int GetTypeId();
	void SetTypeId(int id);
	void SetHighlight(bool state);
	void SetTextureId(TileTexId id);
	void SetPosition(int x, int y);
	int GetPositionX();
	int GetPositionY();
	int GetIndexCount();
	ID3D10ShaderResourceView* GetTexture();

private:
	bool InitialiseBuffers(ID3D10Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(unsigned int screenWidth, unsigned int screenHeight);
	void RenderBuffers(ID3D10Device*);

private:
	ID3D10Buffer *m_VertexBuffer, *m_IndexBuffer;
	int m_VertexCount, m_IndexCount;
	TextureClass* m_Texture;
	int m_PreviousPosX, m_PreviousPosY;
	int m_TypeId; // the primary type of the tile
	TileTexId m_TextureId; // the texture tile id
	int m_PosX;
	int m_PosY;
	bool m_Highlight;
};

#endif