#include <vector>

struct SpriteVertex
{
	float topLeft[2];
	float dimensions[2];
	float opacity;	
};



class Map
{
public:
	Map(void);
	~Map(void);

	std::vector<SpriteVertex>* GetSprites(void);

private:
	std::vector<SpriteVertex> m_Tiles;
};



class StandardRenderer
{
public:
	StandardRenderer(void);
	~StandardRenderer(void);
		
	void SetSprites(std::vector<SpriteVertex>* sprites);

private:
	std::vector<SpriteVertex>* m_SpriteList;
};
