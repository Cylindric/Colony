#pragma once

#include <Windows.h>
#include "StandardRenderer.h"
#include "DirectX9Renderer.h"

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
	};

}