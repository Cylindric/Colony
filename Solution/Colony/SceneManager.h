#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_


#include "global.h"

namespace Ogre
{
	class Root;
	class RenderWindow;
}

namespace Colony
{
	class Map;

	class SceneManager
	{
	public:
		SceneManager(void);
		~SceneManager(void);

		void Initialise(Ogre::Root* root, Ogre::RenderWindow* window);

	private:
		Ogre::Root* mRoot;
		Map* mMap;

	};

}

#endif