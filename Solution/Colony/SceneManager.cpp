#include "SceneManager.h"

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreWindowEventUtilities.h>


namespace Colony
{
	SceneManager::SceneManager()
	{
	}


	SceneManager::~SceneManager()
	{
	}


	void SceneManager::Initialise(Ogre::Root* root)
	{
		Ogre::SceneManager* mSceneManager = root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
	}
}