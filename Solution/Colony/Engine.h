#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <memory>
#include "global.h"


namespace Ogre
{
	class RenderWindow;
	class RenderSystem;
	class Root;
}


namespace Colony
{

	class Engine
	{
	private: // preven accidental copying
		Engine(const Engine& e);
		Engine& operator=(const Engine& s);

	public:
		Engine(void);
		~Engine(void);

		bool Initialise(void);
		void Run(void);

	private:

		Ogre::RenderWindow* mWindow;
		std::auto_ptr<Ogre::Root> mRoot;
	};

}

#endif