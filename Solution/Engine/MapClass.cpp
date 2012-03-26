#include <iostream>
#include <sstream>

#include "MapClass.h"

#include "TextureClass.h"
#include "TileClass.h"
#include "TextureShaderClass.h"

using namespace std;

MapClass::MapClass(void)
{
	m_Texture = 0;
	m_TextureFile = L"";
	m_MapFile = L"";
}


MapClass::~MapClass(void)
{
}


bool MapClass::Initialise(ID3D10Device* device, WCHAR* mapFile)
{
	bool result;
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	result = LoadFromFile(device, mapFile);
	if(!result)
	{
		cerr << "Error loading map " << mapFile << endl;
		return false;
	}

	// initialise a bunch of tiles
	//TileClass* t;
	//for(int row = 0; row < 10; row++)
	//{
	//	for(int col = 0; col < 15; col++)
	//	{
	//		t = new TileClass();
	//		t->Initialize(device, screenWidth, screenHeight, m_Texture);
	//		t->SetTypeId(TILE_TYPE_WALL);
	//		t->SetTextureId((rand() % 16)+16);
	//		t->SetPosition(col, row);
	//		m_Tiles.push_back(t);
	//	}
	//}

	return true;
}


bool MapClass::Render(ID3D10Device* device, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX orthoMatrix, TextureShaderClass* textureShader)
{
	bool result;

	for(vector<TileClass*>::iterator i = m_Tiles.begin(); i < m_Tiles.end(); i++)
	{
		result = (*i)->Render(device);
		if(!result)
		{
			return false;
		}
		textureShader->Render(device, (*i)->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Texture->GetTexture());
	}

	return true;
}


void MapClass::Shutdown(void)
{
	for(vector<TileClass*>::iterator i = m_Tiles.begin(); i < m_Tiles.end(); i++)
	{
		(*i)->Shutdown();
	}
	m_Tiles.clear();
}


bool MapClass::LoadFromFile(ID3D10Device* device, WCHAR* filename)
{
	bool result;

	m_MapFile = filename;

	m_Tiles.clear();

	// open the map file
	wifstream mapFile(m_MapFile, ifstream::in);

	// First value must be the tileset
	mapFile >> m_TextureFile;

	// The size of a single tile
	mapFile >> m_TileSize;

	result = m_Texture->Initialise(device, m_TextureFile);
	if(!result)
	{
		cerr << "Error loading map tileset" << endl;
		return false;
	}
	cout << "Loaded tileset: " << m_TextureFile.c_str() << endl;


	// Next is the width and height of the map
	mapFile >> m_MapWidth >> m_MapHeight;
	cout << "Dimensions: " << m_MapWidth << "x" << m_MapHeight << endl;

	// Next should be lines of tiles
	unsigned int tileCount = 0;
	while (tileCount < (m_MapWidth * m_MapHeight)) {
		WCHAR c = ' ';
		int row = (tileCount / m_MapWidth);
		int col = (tileCount % m_MapWidth);

		// read the next map character into c
		mapFile >> c;

		TileClass* t = new TileClass();
		t->SetPosition(col, row);
		switch (c) 
		{
		case '.':
			t->SetTypeId(TILE_TYPE_OPEN);
			t->SetTextureId(0);
			break;
		case '#':
			t->SetTypeId(TILE_TYPE_WALL);
			t->SetTextureId(31);
			break;
		}
		m_Tiles.push_back(t);
		tileCount++;
	}

	mapFile.close();

	// process walls
	bool wallN, wallS, wallE, wallW;
	TileClass* tileN;
	TileClass* tileE;
	TileClass* tileS;
	TileClass* tileW;

	for (unsigned int row = 0; row < m_MapHeight; row++)
	{
		for (unsigned int col = 0; col < m_MapWidth; col++)
		{
			TileClass* tile = GetTileAt(col, row);

			if (tile->GetTypeId() == TILE_TYPE_WALL)
			{
				char walls = 0;

				// out-of-bounds tiles default to "not a wall"
				wallN = false;
				wallS = false;
				wallE = false;
				wallW = false;

				if(row > 0)
				{
					tileS = GetTileAt(col, row - 1);
					wallS = (tileS->GetTypeId() == TILE_TYPE_WALL);
				}
				if(row < m_MapHeight - 1)
				{
					tileN = GetTileAt(col, row + 1);
					wallN = (tileN->GetTypeId() == TILE_TYPE_WALL);
				}
				if(col > 0)
				{
					tileE = GetTileAt(col - 1, row);
					wallE = (tileE->GetTypeId() == TILE_TYPE_WALL);
				}
				if(col < m_MapWidth - 1)
				{
					tileW = GetTileAt(col + 1, row);
					wallW = (tileW->GetTypeId() == TILE_TYPE_WALL);
				}


				// accumulate all the neighbouring walls into the bit-list
				if (wallS) walls += DIRECTION_S;
				if (wallN) walls += DIRECTION_N;
				if (wallW) walls += DIRECTION_W;
				if (wallE) walls += DIRECTION_E;

				// work out what sort of wall to draw in the current cell
				if (walls == DIRECTION_E) tile->SetTextureId(16); // end
				if (walls == DIRECTION_S) tile->SetTextureId(17); // end
				if (walls == DIRECTION_N) tile->SetTextureId(18); // end
				if (walls == DIRECTION_W) tile->SetTextureId(19); // end

				if (walls == (DIRECTION_E + DIRECTION_S)) tile->SetTextureId(20); // corner
				if (walls == (DIRECTION_W + DIRECTION_S)) tile->SetTextureId(21); // corner
				if (walls == (DIRECTION_N + DIRECTION_E)) tile->SetTextureId(22); // corner
				if (walls == (DIRECTION_N + DIRECTION_W)) tile->SetTextureId(23); // corner

				if (walls == (DIRECTION_N + DIRECTION_S + DIRECTION_E)) tile->SetTextureId(24); // tee
				if (walls == (DIRECTION_E + DIRECTION_S + DIRECTION_W)) tile->SetTextureId(25); // tee
				if (walls == (DIRECTION_E + DIRECTION_N + DIRECTION_W)) tile->SetTextureId(26); // tee
				if (walls == (DIRECTION_N + DIRECTION_S + DIRECTION_W)) tile->SetTextureId(27); // tee

				if (walls == (DIRECTION_N + DIRECTION_S)) tile->SetTextureId(28); // straight
				if (walls == (DIRECTION_E + DIRECTION_W)) tile->SetTextureId(29); // straight

				if (walls == (DIRECTION_N + DIRECTION_S + DIRECTION_W + DIRECTION_E)) tile->SetTextureId(30); // cross

				if (walls == 0) tile->SetTextureId(31); // single

			}
		}
	}


	return true;
}


TileClass* MapClass::GetTileAt(unsigned int x, unsigned int y)
{
	return m_Tiles[(y*m_MapWidth) + x];
}
