#include "StandardRenderer.h"

namespace Core
{
	StandardRenderer::StandardRenderer(void)
	{
	}


	StandardRenderer::~StandardRenderer(void)
	{
	}


	bool StandardRenderer::FatalError(LPCSTR msg)
	{
		MessageBox(*hWnd, msg, "Fatal Error!", MB_ICONERROR);
		return false;
	}

}