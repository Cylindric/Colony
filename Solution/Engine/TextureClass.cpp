////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TextureClass.h"

using namespace std;

TextureClass::TextureClass()
{
	m_texture = 0;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}


bool TextureClass::Initialise(ID3D10Device* device, wstring filename)
{
	HRESULT result;


	// Load the texture in.
	result = D3DX10CreateShaderResourceViewFromFile(device, filename.c_str(), NULL, NULL, &m_texture, NULL);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void TextureClass::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


ID3D10ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}