#ifndef _CMAP_H_
#define _CMAP_H_

// includes
#include <vector>
#include <GL/glew.h>
using namespace std;

// forward declarations
class CTile;

// the class
class CMap
{
public:
	static CMap* getInstance();
	bool onInit(char* filename);
	void onRender();
    vector<CTile*> getTiles(void);

private:
	CMap(void);
	~CMap(void);
	static CMap* instance;
	vector<CTile*> tiles;
	unsigned int tileColumns;
	unsigned int tileRows;
		
	unsigned int tileSize;
	unsigned int tilesetColumns;
	string tilesetFilename;
	GLuint tilesetTextureId;
};

#endif