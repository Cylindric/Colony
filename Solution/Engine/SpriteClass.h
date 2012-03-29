////////////////////////////////////////////////////////////////////////////////
// Filename: SpriteClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SPRITECLASS_H_
#define _SPRITECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <D3DX10.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TextureClass.h"
#include "TextureShaderClass.h"


/////////////
// GLOBALS //
/////////////
static const int SPRITE_SIZE = 32;

enum SpriteTexId
{
	SPRITE_TEX_GROUND = 0,
	SPRITE_TEX_WALL_E = 16,
	SPRITE_TEX_WALL_S = 17,
	SPRITE_TEX_WALL_N = 18,
	SPRITE_TEX_WALL_W = 19,
	SPRITE_TEX_WALL_ES = 20,
	SPRITE_TEX_WALL_SW = 21,
	SPRITE_TEX_WALL_NE = 22,
	SPRITE_TEX_WALL_NW = 23,
	SPRITE_TEX_WALL_NES = 24,
	SPRITE_TEX_WALL_ESW = 25,
	SPRITE_TEX_WALL_NEW = 26,
	SPRITE_TEX_WALL_NSW = 27,
	SPRITE_TEX_WALL_NS = 28,
	SPRITE_TEX_WALL_EW = 29,
	SPRITE_TEX_WALL_NESW = 30,
	SPRITE_TEX_WALL_POST = 31,
	SPRITE_TEX_HIGHLIGHT = 32
};

enum Directions
{
	DIRECTION_N = 1,
	DIRECTION_E = 2,
	DIRECTION_S = 4,
	DIRECTION_W = 8
};


////////////////////////////////////////////////////////////////////////////////
// Class name: SpriteClass
////////////////////////////////////////////////////////////////////////////////
class SpriteClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
	};

public:
	SpriteClass();
	SpriteClass(const SpriteClass&);
	~SpriteClass();

	// Methods
	bool Initialise(ID3D10Device* device, TextureClass* texture, TextureShaderClass* textureShader);
	void Shutdown();
	bool Render(ID3D10Device* device, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX orthoMatrix, unsigned int screenWidth, unsigned int screenHeight);

	// Properties
	void SetTextureId(SpriteTexId id);
	void SetPosition(int x, int y);
	int GetPositionX();
	int GetPositionY();
	int GetIndexCount();
	TextureClass* GetTexture();
	TextureShaderClass* GetTextureShader();

private:
	bool InitialiseBuffers(ID3D10Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(unsigned int screenWidth, unsigned int screenHeight);
	void RenderBuffers(ID3D10Device*);

private:
	ID3D10Buffer *m_VertexBuffer, *m_IndexBuffer;
	int m_VertexCount, m_IndexCount;
	TextureClass* m_Texture;
	TextureShaderClass* m_TextureShader;
	int m_PreviousPosX, m_PreviousPosY;
	SpriteTexId m_TextureId;
	int m_PosX;
	int m_PosY;
};

#endif