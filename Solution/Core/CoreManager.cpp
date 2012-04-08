#include "CoreManager.h"

namespace Core
{

	CoreManager::CoreManager(char* type)
	{
		DEBUG_OUT("CoreManager::Constructor");

		// Set up the renderer
		m_Renderer = NULL;
		if(type == "dx9")
		{
			m_Renderer = new DirectX9Renderer;
		}
		else
		{
			m_Renderer = new DirectX10Renderer;
		}

		// Set up the other objects
		m_TestMode = TEST_MODE_NONE;
		m_FrameCounter = 0;
		m_FrameCounterText = 0;
		m_Map = NULL;
		m_Text = NULL;
		m_Font = NULL;
		m_Input = NULL;
		m_LastFrameTime = 0;
	}


	CoreManager::~CoreManager()
	{
		DEBUG_OUT("CoreManager::Destructor");
		_CrtDumpMemoryLeaks();
	}


	bool CoreManager::Initialise(HWND* handle, TEST_MODE mode)
	{
		DEBUG_OUT("CoreManager::Initialise");

		m_TestMode = mode;

		m_Timer.Start();

		if(!m_Renderer->Initialise(handle)) return false;

		m_Input = new Input;
		if(!m_Input->Initialise()) return false;

		m_Font = new Font;
		if(!m_Font->Initialise("./fonts/default.txt", StandardRenderer::TEXTURE_FONT)) return false;

		m_Text = new Text;
		if(!m_Text->Initialise(m_Font)) return false;

		m_Map = new Map;
		if(!m_Map->Initialise(m_Renderer->GetScreenWidth(), m_Renderer->GetScreenHeight())) return false;


		// Create a frame-counter text object
		m_TextHandles.insert(std::pair<std::string, int>("framecounter", m_Text->InitialiseSentence()));
		m_Text->UpdateSentence(m_TextHandles["framecounter"], "no frames", 2, 12, 1.0f);
		m_TextHandles.insert(std::pair<std::string, int>("fps", m_Text->InitialiseSentence()));
		m_Text->UpdateSentence(m_TextHandles["fps"], "FPS: 0", 2, 23, 1.0f);

		switch(m_TestMode)
		{
		case TEST_MODE_TEXT: 
			m_TextHandles.insert(std::pair<std::string, int>("test1", m_Text->InitialiseSentence()));
			m_Text->UpdateSentence(m_TextHandles["test1"], "This is a test sentence", 100, 300, 1.0f);

			m_TextHandles.insert(std::pair<std::string, int>("test2", m_Text->InitialiseSentence()));
			m_Text->UpdateSentence(m_TextHandles["test2"], "This is a bigger sentence", 100, 100, 3.0f);
			
			m_TestMove[0] = 100.0f;
			m_TestMove[1] = 100.0f;
			m_TestMove[2] = 0.03f;
			m_TestMove[3] = 0.03f;
			m_TextHandles.insert(std::pair<std::string, int>("test_move", m_Text->InitialiseSentence()));
			m_Text->UpdateSentence(m_TextHandles["test2"], "This is a moving sentence", (int)m_TestMove[0], (int)m_TestMove[1], 1.0f);
			break;
		case TEST_MODE_TILES:
			m_Map->CreateRandomTiles(3, 3);
			break;
		}

		return true;
	}


	void CoreManager::Release()
	{
		DEBUG_OUT("CoreManager::Release");

		if(m_Map)
		{
			m_Map->Release();
			delete m_Map;
			m_Map = NULL;
		}

		// Text handles
		m_TextHandles.clear();

		if(m_Text)
		{
			m_Text->Release();
			delete m_Text;
			m_Text = NULL;
		}

		if(m_Font)
		{
			m_Font->Release();
			delete m_Font;
			m_Font = NULL;
		}

		if(m_Input)
		{
			m_Input->Release();
			delete m_Input;
			m_Input = NULL;
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
		// update the frame counter
		m_FrameCounter++;
		double thisFrameTime = m_Timer.GetElapsedTimeSeconds();
		double delta = thisFrameTime - m_LastFrameTime;
		int fps = (int)(1.0f / (delta));

		m_Text->UpdateSentence(m_TextHandles["fps"], "FPS: ", fps);
		m_Text->UpdateSentence(m_TextHandles["framecounter"], "Frames: ", m_FrameCounter);

		if(m_TestMode == TEST_MODE_TEXT)
		{
			// bounce some text around
			if(m_TestMove[0] >= m_Renderer->GetScreenWidth()) m_TestMove[2] =  m_TestMove[2] * -1;
			if(m_TestMove[1] >= m_Renderer->GetScreenHeight()) m_TestMove[3] = m_TestMove[3] * -1;
			if(m_TestMove[0] >= m_Renderer->GetScreenWidth()) m_TestMove[2] = m_TestMove[2] * -1;
			if(m_TestMove[1] >= m_Renderer->GetScreenHeight()) m_TestMove[3] = m_TestMove[3] * 1;
			m_TestMove[0] += m_TestMove[2];
			m_TestMove[1] += m_TestMove[3];
			m_Text->UpdateSentence(m_TextHandles["test2"], "This is a moving sentence", (int)m_TestMove[0], (int)m_TestMove[1], 1.0f);
		}

		// Update all child objects
		m_Renderer->Update();
		m_Map->Update();
		m_Text->Update();

		// Render
		if(!m_Renderer->BeginRender()) return false;

		if(!m_Renderer->RenderSprites(SPRITE_TYPE_TILE, m_Map->GetSprites(SPRITE_TYPE_TILE))) return false;
		if(!m_Renderer->RenderSprites(SPRITE_TYPE_TEXT, m_Text->GetSprites())) return false;

		if(!m_Renderer->EndRender()) return false;

		m_LastFrameTime = thisFrameTime;

		return true;
	}


	void CoreManager::SetMouseXY(int x, int y)
	{
	}

}