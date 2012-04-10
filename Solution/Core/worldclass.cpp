#include "WorldClass.h"


WorldClass::WorldClass(void)
{
}


WorldClass::~WorldClass(void)
{
}


bool WorldClass::Initialize(ID3D10Device* device)
{
	for(int row = 0; row != 5; ++row)
	{
		for(int col = 0; col != 5; ++col)
		{
			ModelClass* tile = new ModelClass;
			tile->Initialize(device, "./models/cube.txt", L"./textures/seafloor.dds");
			m_Tiles.push_back(tile);
		}
	}
	return true;
}


void WorldClass::Shutdown()
{
	m_Tiles.clear();
}


void WorldClass::Render(ID3D10Device* device)
{
	for(auto t = m_Tiles.begin(); t != m_Tiles.end(); ++t)
	{
		(*t)->Render(device);
	}
}
