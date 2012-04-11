#include "Engine.h"

#include <vector>
#include <exception>

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreWindowEventUtilities.h>

#include "SceneManager.h"


namespace Colony
{

	Engine::Engine()
		:mRoot(NULL), mWindow(NULL)
	{
	}


	Engine::~Engine()
	{
		mWindow = NULL;
		mRoot.reset();
	}


	bool Engine::Initialise()
	{
		bool result = false;
		try
		{
			// Step 1: Create Ogre Root
			Ogre::String lConfigFileName = "";
			Ogre::String lPluginsFileName = "";
			Ogre::String lLogFileName = "Colony.log";

			mRoot = std::auto_ptr<Ogre::Root>(new Ogre::Root(lConfigFileName, lPluginsFileName, lLogFileName));

			// Step 2: Load the plugins
			{
				std::vector<Ogre::String> lPluginNames;
				lPluginNames.push_back("RenderSystem_GL");
				lPluginNames.push_back("Plugin_ParticleFX");
				lPluginNames.push_back("Plugin_OctreeSceneManager");

				for(auto it = lPluginNames.begin(); it != lPluginNames.end(); ++it)
				{
					Ogre::String& lPluginName = (*it);
					if(OGRE_DEBUG_MODE)
					{
						lPluginName.append("_d");
					}
					mRoot->loadPlugin(lPluginName);
				}
			}

			// Step 3: select rendersystem
			{
				const Ogre::RenderSystemList& lRenderSystemList = mRoot->getAvailableRenderers();
				if(lRenderSystemList.size() == 0)
				{
					Ogre::LogManager::getSingleton().logMessage("Sorry, no render system was found.");
					return result;
				}
				Ogre::RenderSystem *lRenderSystem = lRenderSystemList[0];
				mRoot->setRenderSystem(lRenderSystem);
			}

			// Step 4: Initialise the root
			{
				bool lCreateAWindowAutomatically = false;
				Ogre::String lWindowTitle = "";
				Ogre::String lCustomCapacities = "";
				mRoot->initialise(lCreateAWindowAutomatically, lWindowTitle, lCustomCapacities);
			}

			// Step 5: Create a window
			{
				Ogre::String lWindowTitle = "Colony";
				unsigned int lSizeX = 800;
				unsigned int lSizeY = 600;
				bool lFullScreen = false;
				Ogre::NameValuePairList lParams;
				lParams["FSAA"] = "0";
				lParams["vsync"] = "true";
				mWindow = mRoot->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullScreen, &lParams);
			}

			result = true;

		} catch(Ogre::Exception &e)
		{
			std::cerr << "!!!Ogre::Exception!!!" << e.what() << std::endl;
			result = false;
		} catch(std::exception &e)
		{
			std::cerr << "!!!std::Exception!!!" << e.what() << std::endl;
			result = false;
		}

		mSceneManager->Initialise(mRoot.get(), mWindow);

		return result;
	}


	void Engine::Run()
	{
		while(!mWindow->isClosed())
		{
			mWindow->update(false);

			bool lVerticalSync = false;
			mWindow->swapBuffers(lVerticalSync);

			mRoot->renderOneFrame();

			Ogre::WindowEventUtilities::messagePump();
		}
	}

}