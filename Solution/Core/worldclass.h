#pragma once

#include <vector>
#include "ModelClass.h"
using std::vector;

class WorldClass
{

public:
	WorldClass(void);
	~WorldClass(void);


	bool Initialize(ID3D10Device*);
	void Shutdown();
	void Render(ID3D10Device*);

private:
	vector<ModelClass*> m_Tiles;
};

