#include "Map.h"


#include <OGRE/OgreRoot.h>
#include <OGRE/OgreSceneManager.h>
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"


namespace Colony
{

	Map::Map()
	{
		mTestObject = NULL;
	}


	Map::~Map()
	{
	}


	void Map::Initialise(Ogre::Root* root, Ogre::SceneManager* scene)
	{
		Ogre::String lTestObjectName = "TestBox";
		mTestObject = scene->createManualObject(lTestObjectName);

		bool lDoIWantToUpdateItLater = false;
		mTestObject->setDynamic(lDoIWantToUpdateItLater);

		float lSize = 0.7f;
		mTestObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
		{
			float cp = 1.0f * lSize;
			float cm = -1.0f * lSize;

			mTestObject->position(cm, cp, cm);// a vertex
			mTestObject->colour(Ogre::ColourValue(0.0f,1.0f,0.0f,1.0f));
			mTestObject->position(cp, cp, cm);// a vertex
			mTestObject->colour(Ogre::ColourValue(1.0f,1.0f,0.0f,1.0f));
			mTestObject->position(cp, cm, cm);// a vertex
			mTestObject->colour(Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f));
			mTestObject->position(cm, cm, cm);// a vertex
			mTestObject->colour(Ogre::ColourValue(0.0f,0.0f,0.0f,1.0f));
 
			mTestObject->position(cm, cp, cp);// a vertex
			mTestObject->colour(Ogre::ColourValue(0.0f,1.0f,1.0f,1.0f));
			mTestObject->position(cp, cp, cp);// a vertex
			mTestObject->colour(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
			mTestObject->position(cp, cm, cp);// a vertex
			mTestObject->colour(Ogre::ColourValue(1.0f,0.0f,1.0f,1.0f));
			mTestObject->position(cm, cm, cp);// a vertex
			mTestObject->colour(Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));
 
			// face behind / front
			mTestObject->triangle(0,1,2);
			mTestObject->triangle(2,3,0);
			mTestObject->triangle(4,6,5);
			mTestObject->triangle(6,4,7);
 
			// face top / down
			mTestObject->triangle(0,4,5);
			mTestObject->triangle(5,1,0);
			mTestObject->triangle(2,6,7);
			mTestObject->triangle(7,3,2);
 
			// face left / right
			mTestObject->triangle(0,7,4);
			mTestObject->triangle(7,0,3);
			mTestObject->triangle(1,5,6);
			mTestObject->triangle(6,2,1);	
		}
		mTestObject->end();

		mTestObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
		{
			float lAxeSize = 2.0f * lSize;
			mTestObject->position(0.0f, 0.0f, 0.0f);
			mTestObject->colour(Ogre::ColourValue::Red);
			mTestObject->position(lAxeSize, 0.0f, 0.0f);
			mTestObject->colour(Ogre::ColourValue::Red);
			mTestObject->position(0.0f, 0.0f, 0.0f);
			mTestObject->colour(Ogre::ColourValue::Green);
			mTestObject->position(0.0, lAxeSize, 0.0);
			mTestObject->colour(Ogre::ColourValue::Green);
			mTestObject->position(0.0f, 0.0f, 0.0f);
			mTestObject->colour(Ogre::ColourValue::Blue);
			mTestObject->position(0.0, 0.0, lAxeSize);
			mTestObject->colour(Ogre::ColourValue::Blue);
 
			mTestObject->index(0);
			mTestObject->index(1);
			mTestObject->index(2);
			mTestObject->index(3);
			mTestObject->index(4);
			mTestObject->index(5);
		}
		mTestObject->end();

		Ogre::String lTestMeshName = "MeshCubeAndAxe";
		Ogre::String lResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		mTestObject->convertToMesh(lTestMeshName);

		Ogre::Entity* lEntity = scene->createEntity(lTestMeshName);
		Ogre::SceneNode* lNode = scene->getRootSceneNode()->createChildSceneNode();
		lNode->attachObject(lEntity);
	}


}
