#include "SceneManager.h"

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreWindowEventUtilities.h>


#include "Map.h"


namespace Colony
{
	SceneManager::SceneManager()
	{
		mMap = NULL;
	}


	SceneManager::~SceneManager()
	{
	}


	void SceneManager::Initialise(Ogre::Root* root, Ogre::RenderWindow* window)
	{
		Ogre::SceneManager* lScene = root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
		Ogre::SceneNode* lRootSceneNode = lScene->getRootSceneNode();
		Ogre::Camera* lCamera = lScene->createCamera("MainCamera");
		Ogre::SceneNode* lCameraNode = lRootSceneNode->createChildSceneNode("MainCameraNode");
		lCameraNode->attachObject(lCamera);

		float lViewportWidth = 0.88f;
		float lViewportHeight = 0.88f;
		float lViewportLeft = (1.0f - lViewportWidth) * 0.5f;
		float lViewportTop = (1.0f - lViewportHeight) * 0.5f;
		unsigned short lMainViewportZOrder = 100;

		Ogre::Viewport* vp = window->addViewport(lCamera, lMainViewportZOrder, lViewportLeft, lViewportTop, lViewportWidth, lViewportHeight);

		vp->setAutoUpdated(true);
		vp->setBackgroundColour(Ogre::ColourValue(1, 0, 1));

		float ratio = float(vp->getActualWidth()) / float(vp->getActualHeight());
		lCamera->setAspectRatio(ratio);
		lCamera->setNearClipDistance(1.5f);
		lCamera->setFarClipDistance(3000.0f);

		window->setActive(true);
		window->setAutoUpdated(false);

		root->clearEventTimes();

		mMap = new Map;

		mMap->Initialise(root, lScene);
	}
}