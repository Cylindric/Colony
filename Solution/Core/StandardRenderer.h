#pragma once

#include <Windows.h>
#include <vector>
#include "VertexTypes.h"

namespace Core
{
	class StandardRenderer
	{
	public:
		StandardRenderer(void);
		~StandardRenderer(void);

		virtual bool Initialise(HWND* handle) = 0;
		virtual void Release(void) = 0;
		virtual bool Render(void) = 0;
		
		void SetSprites(std::vector<SpriteVertex>* sprites);

	protected:
		HWND* hWnd;

		// sprite container
		std::vector<SpriteVertex>* m_SpriteList;

		//fatal error handler
		bool FatalError(LPCSTR msg); 
	};
}