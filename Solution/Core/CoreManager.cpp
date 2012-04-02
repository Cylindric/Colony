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
		m_TestText = 0;
		m_Map = NULL;
		m_Text = NULL;
		m_Font = NULL;
	}


	CoreManager::~CoreManager()
	{
	}


	bool CoreManager::Initialise(HWND* handle)
	{
		if(!m_Renderer->Initialise(handle)) return false;

		m_Font = new Font;
		if(!m_Font->Initialise("./fonts/default.txt", StandardRenderer::TEXTURE_FONT)) return false;

		m_Text = new Text;
		if(!m_Text->Initialise(m_Font)) return false;

		// add a test text item
		m_TestText = m_Text->InitialiseSentence();


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

		if(m_Text)
		{
			m_Text->Release();
			delete m_Text;
			m_Text = NULL;
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
		m_Text->Update();

		// Render
		if(!m_Renderer->BeginRender()) return false;

		//if(!m_Renderer->RenderSprites(SPRITE_TYPE_TILE, m_Map->GetSprites(SPRITE_TYPE_TILE))) return false;
		if(!m_Renderer->RenderSprites(SPRITE_TYPE_TEXT, m_Text->GetSprites())) return false;

		if(!m_Renderer->EndRender()) return false;
		return true;
	}

}