#include "DirectX9Renderer.h"


namespace Core
{

	DirectX9Renderer::DirectX9Renderer(void)
	{
		pD3DDevice = NULL;
		pSwapChain = NULL;
		pRenderTargetView = NULL;
	}


	DirectX9Renderer::~DirectX9Renderer(void)
	{
	}


	bool DirectX9Renderer::Initialise(HWND* handle)
	{
		//window handle
		hWnd = handle;
	
		//get window dimensions
		RECT rc;
		GetClientRect( *hWnd, &rc );
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		//Set up DX swap chain
		//--------------------------------------------------------------
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	
		//set buffer dimensions and format
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;
	
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
		HRESULT result = D3D10CreateDeviceAndSwapChain1(
			NULL, 
			D3D10_DRIVER_TYPE_HARDWARE,
			NULL, 
			0,
			D3D10_FEATURE_LEVEL_9_1,
			D3D10_1_SDK_VERSION,
			&swapChainDesc, 
			&pSwapChain,
			&pD3DDevice
		);
		if(FAILED(result))
		{
			return FatalError("D3D device creation failed");
		}

		//Create render target view
		//--------------------------------------------------------------
	
		//try to get the back buffer
		ID3D10Texture2D* pBackBuffer;	
		if ( FAILED( pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer) ) ) return FatalError("Could not get back buffer");

		//try to create render target view
		if ( FAILED( pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView) ) ) return FatalError("Could not create render target view");

		//release the back buffer
		pBackBuffer->Release();

		//set the render target
		pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);
	
		//Create viewport
		//--------------------------------------------------------------
	
		//create viewport structure	
		viewPort.Width = width;
		viewPort.Height = height;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;

		//set the viewport
		pD3DDevice->RSSetViewports(1, &viewPort);

		// Set up the view matrix
		//--------------------------------------------------------------
		D3DXVECTOR3 camera[3] = {	D3DXVECTOR3(0.0f, 0.0f, -5.0f),
									D3DXVECTOR3(0.0f, 0.0f, 1.0f),
									D3DXVECTOR3(0.0f, 1.0f, 0.0f) };
		D3DXMatrixLookAtLH(&viewMatrix, &camera[0], &camera[1], &camera[2]);
		
		//Set up projection matrix
		//--------------------------------------------------------------
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, (float)D3DX_PI * 0.5f, (float)width/(float)height, 0.1f, 100.0f);
		
		//everything completed successfully
		return true;
	}


	void DirectX9Renderer::Release()
	{
		if(pRenderTargetView) pRenderTargetView->Release();
		pRenderTargetView = NULL;

		if(pSwapChain) pSwapChain->Release();
		pSwapChain = NULL;

		if(pD3DDevice) pD3DDevice->Release();
		pD3DDevice = NULL;
	}


	bool DirectX9Renderer::Update()
	{
		return true;
	}


	bool DirectX9Renderer::BeginRender()
	{
		pD3DDevice->ClearRenderTargetView( pRenderTargetView, D3DXCOLOR(0,0,0,0) );
		return true;
	}


	bool DirectX9Renderer::EndRender()
	{
		pSwapChain->Present(0,0);
		return true;
	}


	bool DirectX9Renderer::RenderSprites(SpriteType type, std::vector<SpriteVertex>* sprites)
	{
		return true;
	}

}