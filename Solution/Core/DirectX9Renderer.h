#pragma once


/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d10_1.lib")
#ifdef DEBUG
#pragma comment(lib, "d3dx10d.lib")
#else
#pragma comment(lib, "d3dx10.lib")
#endif


//////////////
// INCLUDES //
//////////////
#include <Windows.h>
#include <D3D10_1.h>
#include <D3DX10.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "StandardRenderer.h"


namespace Core
{

	class DirectX9Renderer : public StandardRenderer
	{
	public:
		DirectX9Renderer(void);
		~DirectX9Renderer(void);

		bool Initialise(HWND* handle);
		void Release(void);
		bool BeginRender(void);
		bool RenderSprites(SpriteType type, std::vector<SpriteVertex>* sprites);
		bool EndRender(void);

	private:
		//device vars
		ID3D10Device1*				pD3DDevice;
		IDXGISwapChain*				pSwapChain;
		ID3D10RenderTargetView*		pRenderTargetView;
		D3D10_VIEWPORT				viewPort;
	
		//projection and view matrices
		D3DXMATRIX                  viewMatrix;
		D3DXMATRIX                  projectionMatrix;

	};

}