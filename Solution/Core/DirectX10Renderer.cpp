#include "DirectX10Renderer.h"


namespace Core
{

	DirectX10Renderer::DirectX10Renderer(void)
	{
		DEBUG_OUT("DirectX10Renderer::Constructor");
		pD3DDevice = NULL;
		pSwapChain = NULL;
		pRenderTargetView = NULL;
		m_SpriteEffect = NULL;
		m_SpriteBuffer = NULL;
	}


	DirectX10Renderer::~DirectX10Renderer(void)
	{
		DEBUG_OUT("DirectX10Renderer::Destructor");
	}


	bool DirectX10Renderer::Initialise(HWND* handle)
	{
		DEBUG_OUT("DirectX10Renderer::Initialise");

		//window handle
		hWnd = handle;
	
		//get window dimensions
		RECT rc;
		GetClientRect( *hWnd, &rc );
		m_ScreenWidth = rc.right - rc.left;
		m_ScreenHeight = rc.bottom - rc.top;

		if(!CreateSwapChainAndDevice()) return false;
		if(!ResizeScreen()) return false;
		if(!LoadShadersAndCreateInputLayouts()) return false;
		if(!InitialiseBuffers()) return false;

		// Load textures
		if(FAILED(D3DX10CreateShaderResourceViewFromFile(pD3DDevice, "./textures/tiles.png", NULL, NULL,  &m_SpriteTexture, NULL)))
		{
			return FatalError("Could not load sprite texture");
		}

		if(FAILED(D3DX10CreateShaderResourceViewFromFile(pD3DDevice, "./fonts/default.png", NULL, NULL,  &m_FontTexture, NULL)))
		{
			return FatalError("Could not load font texture");
		}

		//everything completed successfully
		return true;
	}


	bool DirectX10Renderer::InitialiseBuffers()
	{
		m_SpriteVertices.reserve(SPRITE_BUFFER_SIZE);

		SpriteVertex* vertices = new SpriteVertex[SPRITE_BUFFER_SIZE];
		memset(vertices, 0, (sizeof(SpriteVertex)*SPRITE_BUFFER_SIZE));

		D3D10_SUBRESOURCE_DATA initData;
		initData.pSysMem = vertices;

		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(SpriteVertex)*(SPRITE_BUFFER_SIZE);
		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		if(FAILED(pD3DDevice->CreateBuffer(&bd, &initData, &m_SpriteBuffer)))
		{
			return false;
		}

		delete [] vertices;
		vertices = 0;

		return true;
	}


	bool DirectX10Renderer::UpdateBuffers(SpriteVector* sprites)
	{
		if(sprites->size() <= SPRITE_BUFFER_SIZE)
		{
			m_SpriteVertices = *sprites;
		}
		else
		{
			return false;
		}

		void* verticesPtr;
		verticesPtr = 0;
		m_SpriteBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr);
		memcpy(verticesPtr, (void*)&((*sprites)[0]), sizeof(SpriteVertex) * sprites->size());
		m_SpriteBuffer->Unmap();

		return true;
	}


	void DirectX10Renderer::Release()
	{
		DEBUG_OUT("DirectX10Renderer::Release");

		if(pRenderTargetView) pRenderTargetView->Release();
		if(pSwapChain) pSwapChain->Release();
		if(pD3DDevice) pD3DDevice->Release();
		if(m_SpriteEffect) m_SpriteEffect->Release();
		if(pDepthStencil) pDepthStencil->Release();
		
		// release all textures
		if(m_SpriteTexture) m_SpriteTexture->Release();
		if(m_FontTexture) m_FontTexture->Release();

		if(m_SpriteBuffer) m_SpriteBuffer->Release();
		m_SpriteVertices.clear();
	}


	bool DirectX10Renderer::Update()
	{
		RECT rc;
		GetClientRect(*hWnd, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;
		
		if(width != m_ScreenWidth || height != m_ScreenHeight)
		{
			if(!ResizeScreen())
			{
				FatalError("Could not resize screen!");
				return false;
			}
		}
		return true;
	}


	bool DirectX10Renderer::ResizeScreen()
	{
		DEBUG_OUT("DirectX10Renderer::ResizeScreen");

		//If there is a valid render target
		if(pRenderTargetView)
		{
			pRenderTargetView->Release();
		}
    
		//Resize the swap chain's buffer to the given dimensions
		pSwapChain->ResizeBuffers(
			2, 
			m_ScreenWidth, m_ScreenHeight, 
			DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
		);
        
		ID3D10Texture2D *pBufferTexture(NULL);

		//Get the swap chain's primary backbuffer (index 0)
		HRESULT hr(pSwapChain->GetBuffer(
			0,
			__uuidof(ID3D10Texture2D),
			(LPVOID*) &pBufferTexture
		));

		//If no buffer was retrieved
		if(FAILED(hr))
		{
			return FatalError("Failed to retrieve buffer");
		}

		//Create a new render target view using this backbuffer
		hr = pD3DDevice->CreateRenderTargetView(
			pBufferTexture, 
			NULL,
			&pRenderTargetView
		);

		//Release the reference to the backbuffer
		pBufferTexture->Release();

		//If you failed to create a render target view
		if(FAILED(hr))
		{
			return FatalError("Failed to create Render Target View!");
		}
  
		//Create a definition of the viewport
		D3D10_VIEWPORT viewPort;
		viewPort.Width = m_ScreenWidth;
		viewPort.Height = m_ScreenHeight;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;

		//Set the device's viewport
		pD3DDevice->RSSetViewports(1, &viewPort);
  
		//create a depth stencil texture
		D3D10_TEXTURE2D_DESC descDepth;
		descDepth.Width = m_ScreenWidth;
		descDepth.Height = m_ScreenHeight;
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

		//Set the device's render target to the one just created
		pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

		return true;
	}


	bool DirectX10Renderer::BeginRender()
	{
		//clear scene
#ifdef DEBUG
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f));
#else
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, D3DXCOLOR(0,0,0,0));
#endif
		pD3DDevice->ClearDepthStencilView(pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);

		//set topology
		pD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);

		//return
		return true;
	}


	bool DirectX10Renderer::EndRender()
	{
		//flip buffers
		pSwapChain->Present(0, 0);

		//return
		return true;
	}


	bool DirectX10Renderer::CreateSwapChainAndDevice()
	{
		DEBUG_OUT("DirectX10Renderer::CreateSwapChainAndDevice");

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	
		//set buffer dimensions and format
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = m_ScreenWidth;
		swapChainDesc.BufferDesc.Height = m_ScreenHeight;
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
		DEBUG_OUT("DirectX10Renderer::LoadShadersAndCreateInputLayouts");

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
			&m_SpriteEffect,
			NULL,
			NULL);
		if(FAILED(result))
		{
			return FatalError("Could not load effect file!");
		}

		//get technique and desc
		m_SpriteTechnique = m_SpriteEffect->GetTechniqueByName("RENDER");
		if(m_SpriteTechnique == NULL)
		{
			return FatalError("Could not find technique!");
		}
		m_SpriteTechnique->GetDesc(&m_SpriteTechDesc);

		

		//create texture effect variable
		pColorMap = m_SpriteEffect->GetVariableByName("colorMap")->AsShaderResource();

		//create input layout
		D3D10_PASS_DESC PassDesc;
		m_SpriteTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
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


	bool DirectX10Renderer::RenderSprites(SpriteType type, SpriteVector* sprites)
	{
		if(!sprites)
		{
			return true;
		}

		int numSprites = sprites->size();
		if(numSprites == 0)
		{
			return true;
		}


		//draw sprites
		switch(type)
		{
		case SPRITE_TYPE_TILE:
			pColorMap->SetResource(m_SpriteTexture);
			break;

		case SPRITE_TYPE_TEXT:
			pColorMap->SetResource(m_FontTexture);
			break;

		default:
			pColorMap->SetResource(m_SpriteTexture);
			break;

		}

		// make sure the shader knows the screen-size so it can scale the sprites correctly
		ID3D10EffectVariable* em = m_SpriteEffect->GetVariableByName("screenDimensions");
		int dims[2];
		dims[0] = m_ScreenWidth;
		dims[1] = m_ScreenHeight;
		em->SetRawValue(&dims, 0, sizeof(dims));

		// clear the current sprite buffer
		int remainingSprites = sprites->size();
		SpriteVector spritesToRender;
		SpriteIterator startSprite;
		SpriteIterator endSprite;
		startSprite = sprites->begin();
		while(remainingSprites > 0)
		{
			// get the first batch of sprites
			endSprite = sprites->end();
			if(remainingSprites > SPRITE_BUFFER_SIZE)
			{
				endSprite = startSprite + SPRITE_BUFFER_SIZE;
			}

			std::copy(startSprite, endSprite, std::back_inserter(spritesToRender));

			// draw this batch of sprites
			RenderSpriteRange(&spritesToRender);

			// get ready for the next iteration
			startSprite = endSprite;
			remainingSprites -= SPRITE_BUFFER_SIZE;
			spritesToRender.clear();
		}
		
		return true;
	}


	bool DirectX10Renderer::RenderSpriteRange(SpriteVector* sprites)
	{
		UpdateBuffers(sprites);

		//ID3D10RasterizerState* WireFrame;
		//D3D10_RASTERIZER_DESC wfdesc;
		//ZeroMemory(&wfdesc, sizeof(D3D10_RASTERIZER_DESC));
		//wfdesc.FillMode = D3D10_FILL_WIREFRAME;
		//wfdesc.CullMode = D3D10_CULL_BACK;
		//wfdesc.FrontCounterClockwise = false;
		//HRESULT hr = pD3DDevice->CreateRasterizerState(&wfdesc, &WireFrame);
		//pD3DDevice->RSSetState(WireFrame);

		// Set vertex buffer
		UINT stride = sizeof(SpriteVertex);
		UINT offset = 0;
		pD3DDevice->IASetVertexBuffers(0, 1, &m_SpriteBuffer, &stride, &offset);


		for(UINT p = 0; p < m_SpriteTechDesc.Passes; p++)
		{
			//apply technique
			m_SpriteTechnique->GetPassByIndex(p)->Apply(0);

			//draw
			pD3DDevice->Draw(sprites->size(), 0);
		}

		return true;
	}

}