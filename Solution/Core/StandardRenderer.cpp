#include "StandardRenderer.h"

namespace Core
{
	StandardRenderer::StandardRenderer(void)
	{
	}


	StandardRenderer::~StandardRenderer(void)
	{
	}

	
	void StandardRenderer::SetSprites(std::vector<SpriteVertex>* sprites)
	{
		m_SpriteList = sprites;
	}


	bool StandardRenderer::FatalError(LPCSTR msg)
	{
		MessageBox(*hWnd, msg, "Fatal Error!", MB_ICONERROR);
		return false;
	}

}