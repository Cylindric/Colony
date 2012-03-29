////////////////////////////////////////////////////////////////////////////////
// Filename: MapClass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "MapClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: MapClass
////////////////////////////////////////////////////////////////////////////////
MapClass::MapClass(void)
{
	m_Texture = 0;
	m_TextureFile = L"";
	m_MapFile = L"";
}


MapClass::~MapClass(void)
{
}


bool MapClass::Initialise(ID3D10Device* device, WCHAR* mapFile, TextureShaderClass* textureshader)
{
	bool result;

	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	result = LoadFromFile(device, mapFile, textureshader);
	if(!result)
	{
		cerr << "Error loading map " << mapFile << endl;
		return false;
	}

	return true;
}


bool MapClass::Render(ID3D10Device* device, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX orthoMatrix)
{
	bool result;
	for(vector<TileClass*>::iterator i = m_Tiles.begin(); i < m_Tiles.end(); i++)
	{
		result = (*i)->Render(device, worldMatrix, viewMatrix, orthoMatrix, m_ScreenWidth, m_ScreenHeight);
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


void MapClass::Frame(int screenW, int screenH, int mouseX, int mouseY)
{
	m_ScreenWidth = screenW;
	m_ScreenHeight = screenH;

	// convert the mouse coords to map coords
	//unsigned int tilesAcross = m_ScreenWidth / m_TileSize;
	//unsigned int tilesDown = m_ScreenHeight / m_TileSize;
	//unsigned int tileX = tilesAcross * ((float)mouseX / m_ScreenWidth);
	//unsigned int tileY = tilesDown * ((float)mouseY / m_ScreenHeight);

	//TileClass* t = GetTileAt(tileX, tileY);
	//t->SetHighlight(true);
}


bool MapClass::LoadFromFile(ID3D10Device* device, WCHAR* filename, TextureShaderClass* textureshader)
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
		t->Initialise(device, m_Texture, textureshader);
		t->SetPosition(col, row);
		switch (c) 
		{
		case '.':
			t->SetTypeId(TILE_TYPE_OPEN);
			t->SetTextureId(SPRITE_TEX_GROUND);
			break;
		case '#':
			t->SetTypeId(TILE_TYPE_WALL);
			t->SetTextureId(SPRITE_TEX_WALL_POST);
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
					tileN = GetTileAt(col, row - 1);
					wallN = (tileN->GetTypeId() == TILE_TYPE_WALL);
				}
				if(row < m_MapHeight - 1)
				{
					tileS = GetTileAt(col, row + 1);
					wallS = (tileS->GetTypeId() == TILE_TYPE_WALL);
				}
				if(col > 0)
				{
					tileW = GetTileAt(col - 1, row);
					wallW = (tileW->GetTypeId() == TILE_TYPE_WALL);
				}
				if(col < m_MapWidth - 1)
				{
					tileE = GetTileAt(col + 1, row);
					wallE = (tileE->GetTypeId() == TILE_TYPE_WALL);
				}


				// accumulate all the neighbouring walls into the bit-list
				if (wallS) walls += DIRECTION_S;
				if (wallN) walls += DIRECTION_N;
				if (wallW) walls += DIRECTION_W;
				if (wallE) walls += DIRECTION_E;

				// work out what sort of wall to draw in the current cell
				if (walls == DIRECTION_E) tile->SetTextureId(SPRITE_TEX_WALL_E); // end
				if (walls == DIRECTION_S) tile->SetTextureId(SPRITE_TEX_WALL_S); // end
				if (walls == DIRECTION_N) tile->SetTextureId(SPRITE_TEX_WALL_N); // end
				if (walls == DIRECTION_W) tile->SetTextureId(SPRITE_TEX_WALL_W); // end

				if (walls == (DIRECTION_E + DIRECTION_S)) tile->SetTextureId(SPRITE_TEX_WALL_ES); // corner
				if (walls == (DIRECTION_W + DIRECTION_S)) tile->SetTextureId(SPRITE_TEX_WALL_SW); // corner
				if (walls == (DIRECTION_N + DIRECTION_E)) tile->SetTextureId(SPRITE_TEX_WALL_NE); // corner
				if (walls == (DIRECTION_N + DIRECTION_W)) tile->SetTextureId(SPRITE_TEX_WALL_NW); // corner

				if (walls == (DIRECTION_N + DIRECTION_S + DIRECTION_E)) tile->SetTextureId(SPRITE_TEX_WALL_NES); // tee
				if (walls == (DIRECTION_E + DIRECTION_S + DIRECTION_W)) tile->SetTextureId(SPRITE_TEX_WALL_ESW); // tee
				if (walls == (DIRECTION_E + DIRECTION_N + DIRECTION_W)) tile->SetTextureId(SPRITE_TEX_WALL_NEW); // tee
				if (walls == (DIRECTION_N + DIRECTION_S + DIRECTION_W)) tile->SetTextureId(SPRITE_TEX_WALL_NSW); // tee

				if (walls == (DIRECTION_N + DIRECTION_S)) tile->SetTextureId(SPRITE_TEX_WALL_NS); // straight
				if (walls == (DIRECTION_E + DIRECTION_W)) tile->SetTextureId(SPRITE_TEX_WALL_EW); // straight

				if (walls == (DIRECTION_N + DIRECTION_S + DIRECTION_W + DIRECTION_E)) tile->SetTextureId(SPRITE_TEX_WALL_NESW); // cross

				if (walls == 0) tile->SetTextureId(SPRITE_TEX_WALL_POST); // single

			}
		}
	}


	return true;
}


TileClass* MapClass::GetTileAt(unsigned int x, unsigned int y)
{
	return m_Tiles[(y*m_MapWidth) + x];
}


