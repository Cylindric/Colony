#include "StandardRenderer.h"

namespace Core
{
	StandardRenderer::StandardRenderer(void)
	{
	}


	StandardRenderer::~StandardRenderer(void)
	{
	}


	int StandardRenderer::GetScreenWidth(void)
	{
		return m_ScreenWidth;
	}


	int StandardRenderer::GetScreenHeight(void)
	{
		return m_ScreenHeight;
	}


	bool StandardRenderer::FatalError(LPCSTR msg)
	{
		MessageBox(*hWnd, msg, "Fatal Error!", MB_ICONERROR);
		return false;
	}

}