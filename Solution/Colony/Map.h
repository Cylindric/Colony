#ifndef _MAP_H_
#define _MAP_H_


namespace Ogre
{
	class ManualObject;
	class Root;
	class SceneManager;
}

namespace Colony
{

	class Map
	{
	public:
		Map(void);
		~Map(void);

		void Initialise(Ogre::Root* root, Ogre::SceneManager* scene);
		void Render(void);

	private:
		Ogre::ManualObject* mTestObject;
	};

}

#endif