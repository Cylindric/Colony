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
#include "SpriteClass.h"


/////////////
// GLOBALS //
/////////////
static const int TILE_SIZE = 32;

enum TileType
{
	TILE_TYPE_OPEN = 1,
	TILE_TYPE_WALL = 2
};


////////////////////////////////////////////////////////////////////////////////
// Class name: TileClass
////////////////////////////////////////////////////////////////////////////////
class TileClass : public SpriteClass
{
public:
	TileClass();
	TileClass(const TileClass&);
	~TileClass();

	// Methods
	bool Render(ID3D10Device* device, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX orthoMatrix, unsigned int screenWidth, unsigned int screenHeight);
	void Shutdown();

	// Properties
	int GetTypeId();
	void SetTypeId(int id);
	void SetHighlight(bool state);

private:
	int m_TypeId; // the primary type of the tile
	bool m_Highlight;
	SpriteClass* m_HighlighterSprite;
};

#endif