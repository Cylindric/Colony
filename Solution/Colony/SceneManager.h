#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_


#include "global.h"

namespace Ogre
{
	class Root;
}

namespace Colony
{

	class SceneManager
	{
	public:
		SceneManager(void);
		~SceneManager(void);

		void Initialise(Ogre::Root* root);

	private:
		Ogre::Root* mRoot;

	};

}

#endif