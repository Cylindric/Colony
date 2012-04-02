#pragma once

#include <Windows.h>
#include <vector>
#include "VertexTypes.h"

namespace Core
{
	class StandardRenderer
	{
	public:
		enum TEXTURE_ID
		{
			TEXTURE_NONE = -1,
			TEXTURE_SPRITE = 0,
			TEXTURE_FONT = 1
		};


	public:
		StandardRenderer(void);
		~StandardRenderer(void);

		virtual bool Initialise(HWND* handle) = 0;
		virtual void Release(void) = 0;
		virtual bool BeginRender(void) = 0;
		virtual bool RenderSprites(SpriteType type, std::vector<SpriteVertex>* sprites) = 0;
		virtual bool EndRender(void) = 0;
		
	protected:
		HWND* hWnd;

		//fatal error handler
		bool FatalError(LPCSTR msg); 
	};
}