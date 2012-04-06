#pragma once
#include "global.h"


//////////////
// INCLUDES //
//////////////
#include <map>
#include <Windows.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "StandardRenderer.h"
#include "DirectX9Renderer.h"
#include "DirectX10Renderer.h"
#include "Font.h"
#include "Input.h"
#include "Map.h"
#include "Text.h"
#include "Timer.h"
#include "VertexTypes.h"


namespace Core
{

	class CoreManager
	{
	public:
		enum TEST_MODE
		{
			TEST_MODE_NONE,
			TEST_MODE_TEXT,
			TEST_MODE_TILES
		};

		CoreManager(char* type);
		~CoreManager(void);
		
		bool Initialise(HWND* handle, TEST_MODE mode = TEST_MODE_NONE);
		void Release(void);
		bool Render();

	private:
		StandardRenderer* m_Renderer;
		Map* m_Map;
		Font* m_Font;
		Text* m_Text;
		Input* m_Input;
		Timer m_Timer;

		double m_LastFrameTime;
		int m_FrameCounter;
		int m_FrameCounterText;
		std::map<std::string, int> m_TextHandles;

		// testing
		TEST_MODE m_TestMode;
		float m_TestMove[4];


	};

}