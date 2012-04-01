#include "CoreManager.h"

namespace Core
{

	CoreManager::CoreManager(char* type)
	{
		// Set up the renderer
		m_Renderer = NULL;
		if(type=="dx9")
		{
			m_Renderer = new DirectX9Renderer;
		}
		else if(type=="dx10")
		{
			m_Renderer = new DirectX10Renderer;
		}

		// Set up the other objects
		m_Map = NULL;
	}


	CoreManager::~CoreManager()
	{
	}


	bool CoreManager::Initialise(HWND* handle)
	{
		if(!m_Renderer->Initialise(handle)) return false;

		m_Map = new Map;
		if(!m_Map->Initialise()) return false;
		return true;
	}


	void CoreManager::Release()
	{
		if(m_Map)
		{
			m_Map->Release();
			delete m_Map;
			m_Map = NULL;
		}

		if(m_Renderer)
		{
			m_Renderer->Release();
			delete m_Renderer;
			m_Renderer = NULL;
		}
	}


	bool CoreManager::Render()
	{
		// Update all child objects
		m_Map->Update();

		// Render
		m_Renderer->SetSprites(m_Map->GetSprites());
		return m_Renderer->Render();
	}

}