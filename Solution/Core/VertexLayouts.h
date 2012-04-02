#pragma once

/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d10.lib")

//////////////
// INCLUDES //
//////////////
#include <d3d10.h>


const D3D10_INPUT_ELEMENT_DESC vertexInputLayout[] = 
{	
	{ "ANCHOR",     0, DXGI_FORMAT_R32G32_FLOAT, 0, 0,                            D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "DIMENSIONS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "SPRITENUM",  0, DXGI_FORMAT_R32_UINT,     0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "OPACITY",    0, DXGI_FORMAT_R32_FLOAT,    0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};

const int vertexInputLayoutNumElements = sizeof(vertexInputLayout)/sizeof(vertexInputLayout[0]);