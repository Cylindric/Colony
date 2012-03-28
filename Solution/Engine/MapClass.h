////////////////////////////////////////////////////////////////////////////////
// Filename: MapClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MAPCLASS_H_
#define _MAPCLASS_H_


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
#include "CameraClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: MapClass
////////////////////////////////////////////////////////////////////////////////
class MapClass
{
public:
	MapClass(void);
	~MapClass(void);
	bool Initialise(ID3D10Device* device, CameraClass* camera, WCHAR* mapFile);
	bool Render(ID3D10Device*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, TextureShaderClass*);
	void Shutdown();

private:
	bool LoadFromFile(ID3D10Device* device, WCHAR* filename);
	TileClass* GetTileAt(unsigned int x, unsigned int y);
	
	std::wstring m_MapFile; // filename of the file holding the map data
	std::wstring m_TextureFile; // filename of the tileset texture file
	unsigned int m_TileSize; // size of a tile in the texture file, in px
	unsigned int m_MapWidth; // width of the map, in tiles
	unsigned int m_MapHeight; // height of the map, in tiles

	CameraClass* m_Camera;
	TextureClass* m_Texture;
	std::vector<TileClass*> m_Tiles;
};

#endif