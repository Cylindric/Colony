#pragma once

#include <Windows.h>
#include "StandardRenderer.h"
#include "DirectX9Renderer.h"
#include "DirectX10Renderer.h"
#include "Map.h"

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
	};

}