#pragma once


//////////////
// INCLUDES //
//////////////
#include <vector>
#include <Windows.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
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
		virtual bool Update(void) = 0;
		virtual bool BeginRender(void) = 0;
		virtual bool RenderSprites(SpriteType type, std::vector<SpriteVertex>* sprites) = 0;
		virtual bool EndRender(void) = 0;
		virtual void SetCameraXY(int x, int y) = 0;
		int GetScreenWidth(void);
		int GetScreenHeight(void);
		
	protected:
		HWND* hWnd;
		UINT m_ScreenWidth;
		UINT m_ScreenHeight;
		UINT m_CameraX;
		UINT m_CameraY;

		//fatal error handler
		bool FatalError(LPCSTR msg); 
	};
}