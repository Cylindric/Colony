#include "DirectX10Renderer.h"


namespace Core
{

	DirectX10Renderer::DirectX10Renderer(void)
	{
		pD3DDevice = NULL;
		pSwapChain = NULL;
		pRenderTargetView = NULL;
		pBasicEffect = NULL;
		m_SpriteList = NULL;
		pTexture1 = NULL;
		pVertexBuffer = NULL;
	}


	DirectX10Renderer::~DirectX10Renderer(void)
	{
	}


	bool DirectX10Renderer::Initialise(HWND* handle)
	{
		//window handle
		hWnd = handle;
	
		//get window dimensions
		RECT rc;
		GetClientRect( *hWnd, &rc );
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		if(!CreateSwapChainAndDevice(width, height)) return false;
		if(!LoadShadersAndCreateInputLayouts()) return false;
		CreateViewports(width, height);
		if(!CreateRenderTargetsAndDepthBuffer(width, height)) return false;

		// Load texture
		if(FAILED(D3DX10CreateShaderResourceViewFromFile(pD3DDevice, "./textures/tile.png", NULL, NULL, &pTexture1, NULL)))
		{
			return FatalError("Could not load sprite texture");
		}

		//everything completed successfully
		return true;
	}


	void DirectX10Renderer::Release(void)
	{
		if(pRenderTargetView) pRenderTargetView->Release();
		if(pSwapChain) pSwapChain->Release();
		if(pD3DDevice) pD3DDevice->Release();
		if(pBasicEffect) pBasicEffect->Release();
		if(pDepthStencil) pDepthStencil->Release();
		if(pTexture1) 
		{
			pTexture1->Release();
		}
		if(pVertexBuffer) pVertexBuffer->Release();
	}


	bool DirectX10Renderer::Render(void)
	{
		bool result = true;

		//clear scene
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, D3DXCOLOR(0,0,0,0));
		pD3DDevice->ClearDepthStencilView(pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);

		//set topology
		pD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);

		//setup sprites
		result = RenderSprites();
		if(!result)
		{
			return false;
		}

		//flip buffers
		pSwapChain->Present(0, 0);

		return result;
	}


	bool DirectX10Renderer::CreateSwapChainAndDevice(UINT width, UINT height)
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	
		//set buffer dimensions and format
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	
		//set refresh rate
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	
		//sampling settings
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SampleDesc.Count = 1;

		//output window handle
		swapChainDesc.OutputWindow = *hWnd;
		swapChainDesc.Windowed = true;    

		//Create the D3D device
		//--------------------------------------------------------------
		HRESULT result = D3D10CreateDeviceAndSwapChain(
			NULL, 
			D3D10_DRIVER_TYPE_HARDWARE,
			NULL, 
			0,
			D3D10_SDK_VERSION,
			&swapChainDesc, 
			&pSwapChain,
			&pD3DDevice
		);
		if(FAILED(result))
		{
			return FatalError("D3D device creation failed");
		}

		return true;
	}


	bool DirectX10Renderer::LoadShadersAndCreateInputLayouts()
	{
		HRESULT result;
		result = D3DX10CreateEffectFromFile(
			"./shaders/sprite.fx",
			NULL, 
			NULL,
			"fx_4_0",
			D3D10_SHADER_ENABLE_STRICTNESS,
			0,
			pD3DDevice,
			NULL,
			NULL,
			&pBasicEffect,
			NULL,
			NULL);
		if(FAILED(result))
		{
			return FatalError("Could not load effect file!");
		}

		//get technique and desc
		pTechnique = pBasicEffect->GetTechniqueByName("RENDER");
		if(pTechnique == NULL)
		{
			return FatalError("Could not find technique!");
		}
		pTechnique->GetDesc(&techDesc);

		//create texture effect variable
		pColorMap = pBasicEffect->GetVariableByName("colorMap")->AsShaderResource();

		//create input layout
		D3D10_PASS_DESC PassDesc;
		pTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
		if(FAILED(pD3DDevice->CreateInputLayout(
			vertexInputLayout,
			vertexInputLayoutNumElements,
			PassDesc.pIAInputSignature,
			PassDesc.IAInputSignatureSize,
			&pVertexLayout)))
		{
			return FatalError("Could not create Input Layout!");
		}

		//Set the input layout
		pD3DDevice->IASetInputLayout(pVertexLayout);

		return true;
	}


	void DirectX10Renderer::CreateViewports(UINT width, UINT height)
	{
		viewPort.Width = width;
		viewPort.Height = height;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;

		//set the viewport
		pD3DDevice->RSSetViewports(1, &viewPort);
	}


	bool DirectX10Renderer::CreateRenderTargetsAndDepthBuffer(UINT width, UINT height)
	{
		//try to get the back buffer
		ID3D10Texture2D* pBackBuffer;	
		if ( FAILED( pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer) ) ) 
		{
			return FatalError("Could not get back buffer");
		}

		//try to create render target view
		if ( FAILED( pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView) ) ) 
		{
			return FatalError("Could not create render target view");
		}

		//create a depth stencil texture
		D3D10_TEXTURE2D_DESC descDepth;
		descDepth.Width = width;
		descDepth.Height = height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D10_USAGE_DEFAULT;
		descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;

		if(FAILED(pD3DDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil)))
		{
			return FatalError("Could not create depth stencil texture");
		}

		//create the depth stencil view
		D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		if(FAILED(pD3DDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &pDepthStencilView)))
		{
			return FatalError("Could not create depth stencil view");
		}

		//set render targets
		pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);

		return true;
	}


	bool DirectX10Renderer::RenderSprites()
	{
#ifdef TEST_WITH_ARRAY
		numSprites = 3;
		SpriteVertex verts[3];
		verts[0].topLeft[0] = 0.0f;
		verts[0].topLeft[1] = 0.0f;
		verts[0].dimensions[0] = 0.08f;
		verts[0].dimensions[1] = 0.106667f;
		verts[0].opacity = 1;

		verts[1].topLeft[0] = 0.08f;
		verts[1].topLeft[1] = 0.0f;
		verts[1].dimensions[0] = 0.08f;
		verts[1].dimensions[1] = 0.106667f;
		verts[1].opacity = 1;

		verts[2].topLeft[0] = 0.16f;
		verts[2].topLeft[1] = 0.0f;
		verts[2].dimensions[0] = 0.08f;
		verts[2].dimensions[1] = 0.106667f;
		verts[2].opacity = 1;	
#else
		if(!m_SpriteList)
		{
			return true;
		}
		numSprites = m_SpriteList->size();
#endif
		if(numSprites == 0)
		{
			return true;
		}


		D3D10_SUBRESOURCE_DATA initData;
#ifdef TEST_WITH_ARRAY
		initData.pSysMem = &verts;
#else
		initData.pSysMem = &(m_SpriteList[0]);
#endif

		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SpriteVertex)*(numSprites);
		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		if(FAILED(pD3DDevice->CreateBuffer(&bd, &initData, &pVertexBuffer)))
		{
			return FatalError("Could not create sprite vertex buffer!");
		}

		// Set vertex buffer
		UINT stride = sizeof(SpriteVertex);
		UINT offset = 0;
		pD3DDevice->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

		//draw sprites
		pColorMap->SetResource(pTexture1);
		for(UINT p = 0; p < techDesc.Passes; p++)
		{
			//apply technique
			pTechnique->GetPassByIndex(p)->Apply(0);

			//draw
			pD3DDevice->Draw(numSprites, 0);
		}
		
#ifdef TEST_WITH_ARRAY
#else
		for(auto it = m_SpriteList->begin(); it != m_SpriteList->end(); ++it)
		{
			std::cout << (*it).topLeft[0] << ":" << (*it).topLeft[1] << "  ";
			std::cout << (*it).dimensions[0] << ":" << (*it).dimensions[1] << "  ";
			std::cout << (*it).opacity << std::endl;
		}
#endif
		return true;
	}
}