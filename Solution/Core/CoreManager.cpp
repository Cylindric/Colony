#include "CoreManager.h"

namespace Core
{

	CoreManager::CoreManager(char* type)
	{
		m_Renderer = NULL;
		if(type=="dx9")
		{
			m_Renderer = new DirectX9Renderer;
		}
	}


	CoreManager::~CoreManager()
	{
	}


	bool CoreManager::Initialise(HWND* handle)
	{
		return m_Renderer->Initialise(handle);
	}


	void CoreManager::Release()
	{
		if(m_Renderer)
		{
			m_Renderer->Release();
			delete m_Renderer;
			m_Renderer = 0;
		}
	}


	bool CoreManager::Render()
	{
		return m_Renderer->Render();
	}

}