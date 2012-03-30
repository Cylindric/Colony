#pragma once

#include <Windows.h>

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

	protected:
		HWND* hWnd;

		//fatal error handler
		bool FatalError(LPCSTR msg); 
	};
}