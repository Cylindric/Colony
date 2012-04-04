#pragma once


//////////////
// INCLUDES //
//////////////
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
#include "VertexTypes.h"


namespace Core
{

	class CoreManager
	{
	public:
		CoreManager(char* type);
		~CoreManager(void);
		
		bool Initialise(HWND* handle, int mode = 0);
		void Release(void);
		bool Render();

	private:
		StandardRenderer* m_Renderer;
		Map* m_Map;
		Font* m_Font;
		Text* m_Text;
		Input* m_Input;

		int m_TestText;
	};

}