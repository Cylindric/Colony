#include "MapClass.h"

#include "TextureClass.h"
#include "TileClass.h"
#include "TextureShaderClass.h"

MapClass::MapClass(void)
{
	m_Texture = 0;
}


MapClass::~MapClass(void)
{
}


bool MapClass::Initialise(ID3D10Device* device, int screenWidth, int screenHeight)
{
	bool result;
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}
	result = m_Texture->Initialize(device, L"Tileset.dds");
	if(!result)
	{
		return false;
	}

	// initialise a bunch of tiles
	TileClass* t;
	for(int row = 0; row < 10; row++)
	{
		for(int col = 0; col < 15; col++)
		{
			t = new TileClass();
			t->Initialize(device, screenWidth, screenHeight, m_Texture);
			t->SetId((rand() % 16)+16);
			t->SetPosition(col, row);
			m_Tiles.push_back(t);
		}
	}

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
