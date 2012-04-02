#pragma once

/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10d.lib")

//////////////
// INCLUDES //
//////////////
#include <vector>
#include <iostream>
#include <Windows.h>
#include <d3d10.h>
#include <D3DX10.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "StandardRenderer.h"
#include "VertexTypes.h"
#include "VertexLayouts.h"

namespace Core
{

	class DirectX10Renderer : public StandardRenderer
	{
	public:
		DirectX10Renderer(void);
		~DirectX10Renderer(void);

		bool Initialise(HWND* handle);
		void Release(void);
		bool Render(void);

	private:
		//device vars
		ID3D10Device*				pD3DDevice;
		IDXGISwapChain*				pSwapChain;
		ID3D10RenderTargetView*		pRenderTargetView;
		ID3D10Texture2D*			pDepthStencil;
		ID3D10DepthStencilView*		pDepthStencilView;	
		D3D10_VIEWPORT				viewPort;
	
		//input layout
		ID3D10InputLayout*			pVertexLayout;

		//effects and techniques
		ID3D10Effect*				m_SpriteEffect;
		ID3D10EffectTechnique*		m_SpriteTechnique;
		ID3D10ShaderResourceView*	m_SpriteTexture;
		ID3D10Buffer*				m_SpriteBuffer;

		//effect variable pointers
		ID3D10EffectShaderResourceVariable* pColorMap;

		//technique
		D3D10_TECHNIQUE_DESC		techDesc;

		//pipeline
		bool CreateSwapChainAndDevice(UINT width, UINT height);
		bool LoadShadersAndCreateInputLayouts(void);
		void CreateViewports(UINT width, UINT height);
		bool CreateRenderTargetsAndDepthBuffer(UINT width, UINT height);
		bool RenderSprites(void);
	};

}