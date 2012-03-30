////////////////////////////////////////////////////////////////////////////////
// Filename: MapClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MAPCLASS_H_
#define _MAPCLASS_H_

#define TILES_IN_VECTOR 0

//////////////
// INCLUDES //
//////////////
#include <string>
#include <iostream>
#include <sstream>
#include <vector>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TextureClass.h"
#include "TileClass.h"
#include "TextureShaderClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: MapClass
////////////////////////////////////////////////////////////////////////////////
class MapClass
{
public:
	MapClass(void);
	~MapClass(void);
	bool Initialise(ID3D10Device* device, WCHAR* mapFile, TextureShaderClass*);
	bool Render(ID3D10Device*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	void Shutdown();
	void Frame(int screenW, int screenH, int mouseX, int mouseY);

private:
	bool LoadFromFile(ID3D10Device* device, WCHAR* filename, TextureShaderClass* textureshader);
	TileClass* GetTileAt(unsigned int x, unsigned int y);
	
	std::wstring m_MapFile; // filename of the file holding the map data
	std::wstring m_TextureFile; // filename of the tileset texture file
	unsigned int m_TileSize; // size of a tile in the texture file, in px
	unsigned int m_MapWidth; // width of the map, in tiles
	unsigned int m_MapHeight; // height of the map, in tiles
	unsigned int m_ScreenWidth; // width of the screen, in px
	unsigned int m_ScreenHeight; // height of the screen, in px
	unsigned int m_NumTiles;

	TextureClass* m_Texture;
	
#if TILES_IN_VECTOR
	std::vector<TileClass*> m_Tiles;
#else
	TileClass** m_Tiles;
#endif
};

#endif