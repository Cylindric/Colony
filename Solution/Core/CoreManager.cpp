#include "CoreManager.h"

namespace Core
{

	CoreManager::CoreManager(char* type)
	{
		DEBUG_OUT("CoreManager::Constructor");

		// Set up the renderer
		m_Renderer = new DirectX10Renderer;

		// Set up the other objects
		m_TestMode = TEST_MODE_NONE;
		m_FrameCounter = 0;
		m_Map = NULL;
		m_Text = NULL;
		m_Font = NULL;
		m_Input = NULL;
		m_MouseX = 0;
		m_MouseY = 0;
		m_MouseL = false;
		m_FrameStep = 0;
		m_LastFrameStart = 0;
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
		m_TextHandles.insert(std::pair<std::string, int>("framecounter", m_Text->InitialiseSentence("Frames: unknown", 2, 12, 1.0f)));

		m_TextHandles.insert(std::pair<std::string, int>("fps", m_Text->InitialiseSentence("FPS: unknown", 2, 24, 1.0f)));
		m_TextHandles.insert(std::pair<std::string, int>("framestep", m_Text->InitialiseSentence("Framestep: unknown", 100, 24, 1.0f)));

		m_TextHandles.insert(std::pair<std::string, int>("mouse", m_Text->InitialiseSentence("Mouse: unknown", 2, 36, 1.0f)));

		switch(m_TestMode)
		{
		case TEST_MODE_TEXT: 
			m_TextHandles.insert(std::pair<std::string, int>("test1", m_Text->InitialiseSentence("This is a test sentence", 100, 300, 1.0f)));
			m_TextHandles.insert(std::pair<std::string, int>("test2", m_Text->InitialiseSentence("This is a bigger sentence", 100, 100, 3.0f)));
			
			m_TestMove[0] = 100.0f;
			m_TestMove[1] = 100.0f;
			m_TestMove[2] = 0.03f;
			m_TestMove[3] = 0.03f;
			m_TextHandles.insert(std::pair<std::string, int>("test_move", m_Text->InitialiseSentence("This is a moving sentence", (int)m_TestMove[0], (int)m_TestMove[1], 1.0f)));
			break;

		case TEST_MODE_TILES:
			m_Map->SetSpriteSizePx(16);
			m_Map->CreateRandomTiles(100, 100);
			break;

		case TEST_MODE_MOUSE:
			m_Map->CreateRandomTiles(1, 1);
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
		double frameStart = m_Timer.GetElapsedTimeSeconds();

		m_FrameStep = (frameStart - m_LastFrameStart);
		m_FrameCounter++;


		static double fpsLastUpdatedAt = 0;
		static int fpsFramesAtLastUpdate = 0;
		if (m_Timer.GetElapsedTimeSeconds() - 1 > fpsLastUpdatedAt)
		{
			double thisFrameTime = m_Timer.GetElapsedTimeSeconds();
			double timeDelta = thisFrameTime - fpsLastUpdatedAt;
			int frameDelta = m_FrameCounter - fpsFramesAtLastUpdate;
			int fps = (int)((float)frameDelta / timeDelta);

			m_Text->UpdateSentence(m_TextHandles["fps"], "FPS: %d", fps);
			fpsFramesAtLastUpdate = m_FrameCounter;
			fpsLastUpdatedAt = m_Timer.GetElapsedTimeSeconds();
			m_Text->UpdateSentence(m_TextHandles["framecounter"], "Frames: %7d", m_FrameCounter);
			m_Text->UpdateSentence(m_TextHandles["framestep"], "Framestep: %f", m_FrameStep);
		}

		m_Text->UpdateSentence(m_TextHandles["mouse"], "Mouse X:%d Y:%d L:%d", m_MouseX, m_MouseY, m_MouseL);

		if(m_TestMode == TEST_MODE_TEXT)
		{
			// bounce some text around
			if(m_TestMove[0] >= m_Renderer->GetScreenWidth()) m_TestMove[2] =  m_TestMove[2] * -1;
			if(m_TestMove[1] >= m_Renderer->GetScreenHeight()) m_TestMove[3] = m_TestMove[3] * -1;
			if(m_TestMove[0] <= 0) m_TestMove[2] = m_TestMove[2] * -1;
			if(m_TestMove[1] <= 0) m_TestMove[3] = m_TestMove[3] * -1;
			m_TestMove[0] += m_TestMove[2];
			m_TestMove[1] += m_TestMove[3];
			m_Text->UpdateSentence(m_TextHandles["test_move"], "This is a moving sentence: %d %d", (int)m_TestMove[0], (int)m_TestMove[1]);
			m_Text->SetSentencePosition(m_TextHandles["test_move"], (int)m_TestMove[0], (int)m_TestMove[1]);
		}

		// Update all child objects
		static float camX = 0;
		static float camY = 0;
		//camX += (100.0f * m_FrameStep);
		m_Renderer->SetCameraXY((int)camX, (int)camY);

		m_Renderer->Update();
		m_Map->Update(m_FrameStep);
		m_Text->Update();

		// Render
		if(!m_Renderer->BeginRender()) return false;

		m_Renderer->SetCameraXY((int)camX, (int)camY);
		if(!m_Renderer->RenderSprites(SPRITE_TYPE_TILE, m_Map->GetSprites(SPRITE_TYPE_TILE))) return false;

		m_Renderer->SetCameraXY(0, 0);
		if(!m_Renderer->RenderSprites(SPRITE_TYPE_TEXT, m_Text->GetSprites())) return false;

		if(!m_Renderer->EndRender()) return false;

		m_LastFrameStart = frameStart;
		return true;
	}


	void CoreManager::SetMouseXY(int x, int y)
	{
		m_MouseX = x;
		m_MouseY = y;
	}


	void CoreManager::SetMouseLButtonState(bool down)
	{
		m_MouseL = down;
	}

}