#pragma once
#include "global.h"

/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d10.lib")
#ifdef DEBUG
#pragma comment(lib, "d3dx10d.lib")
#else
#pragma comment(lib, "d3dx10.lib")
#endif


//////////////
// INCLUDES //
//////////////
#include <vector>
#include <iterator>
#include <map>
#include <iostream>
#include <Windows.h>
#include <D3D10.h>
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
		bool Update(void);
		bool BeginRender(void);
		bool RenderSprites(SpriteType type, std::vector<SpriteVertex>* sprites);
		bool EndRender(void);

	private:
		static const int SPRITE_BUFFER_SIZE = 1024;

		//device vars
		ID3D10Device*				pD3DDevice;
		IDXGISwapChain*				pSwapChain;
		ID3D10RenderTargetView*		pRenderTargetView;
		ID3D10Texture2D*			pDepthStencil;
		ID3D10DepthStencilView*		pDepthStencilView;	
		D3D10_VIEWPORT				viewPort;
	
		//input layout
		ID3D10InputLayout*			pVertexLayout;

		// Sprite buffers textures, effects and techniques
		std::vector<SpriteVertex>	m_SpriteVertices;
		int							m_SpriteBufferSize;
		ID3D10Effect*				m_SpriteEffect;
		ID3D10EffectTechnique*		m_SpriteTechnique;
		ID3D10Buffer*				m_SpriteBuffer;
		D3D10_TECHNIQUE_DESC		m_SpriteTechDesc;

		// Font textures, effects and techniques
		ID3D10ShaderResourceView*	m_SpriteTexture;
		ID3D10ShaderResourceView*	m_FontTexture;

		// Effect variable pointers
		ID3D10EffectShaderResourceVariable* pColorMap;

		// Pipeline
		bool ResizeScreen(void);
		bool CreateSwapChainAndDevice(void);
		bool LoadShadersAndCreateInputLayouts(void);
		bool InitialiseBuffers(void);
		bool UpdateBuffers(SpriteVector* sprites);
		bool DirectX10Renderer::RenderSpriteRange(SpriteVector* sprites);
	};

}