#include "TextureClass.h"


TextureClass::TextureClass()
{
	m_Texture = 0;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}


bool TextureClass::Initialise(ID3D10Device* device, WCHAR* filename)
{
	HRESULT result;

	result = D3DX10CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_Texture, NULL);
	if(FAILED(result))
	{
		return false;
	}
	return true;
}


void TextureClass::Shutdown()
{
	if(m_Texture)
	{
		m_Texture->Release();
		m_Texture = 0;
	}
	return;
}


ID3D10ShaderResourceView* TextureClass::GetTexture()
{
	return m_Texture;
}