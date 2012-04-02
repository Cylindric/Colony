#pragma once

#include <Windows.h>
#include "StandardRenderer.h"
#include "DirectX9Renderer.h"
#include "DirectX10Renderer.h"
#include "Map.h"
#include "Font.h"
#include "Text.h"
#include "VertexTypes.h"

namespace Core
{

	class CoreManager
	{
	public:
		CoreManager(char* type);
		~CoreManager(void);
		
		bool Initialise(HWND* handle);
		void Release(void);
		bool Render(void);

	private:
		StandardRenderer* m_Renderer;
		Map* m_Map;
		Font* m_Font;
		Text* m_Text;

		int m_TestText;
	};

}