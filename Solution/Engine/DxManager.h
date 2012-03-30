#ifndef _DXMANAGER_H_
#define _DXMANAGER_H_

#pragma comment(lib,"d3d10_1.lib")

#include <Windows.h>
#include <D3D10_1.h>
#include <D3DX10.h>

class DxManager
{
	/*******************************************************************
	* Members
	********************************************************************/	
private:

	//window handle
	HWND*						hWnd;
	
	//device vars
	ID3D10Device1*				pD3DDevice;
	IDXGISwapChain*				pSwapChain;
	ID3D10RenderTargetView*		pRenderTargetView;
	D3D10_VIEWPORT				viewPort;
	
	//projection and view matrices
	D3DXMATRIX                  viewMatrix;
	D3DXMATRIX                  projectionMatrix;

	/*******************************************************************
	* Methods
	********************************************************************/	
public:

	//constructor and destructor
	DxManager();
	~DxManager();

	//initialize directx device
	bool initialize(HWND*);	

	//renderScene
	void renderScene();	

private:

	//fatal error handler
	bool fatalError(LPCWSTR msg); 
};

#endif