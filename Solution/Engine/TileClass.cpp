////////////////////////////////////////////////////////////////////////////////
// Filename: TileClass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TileClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: TileClass
////////////////////////////////////////////////////////////////////////////////
TileClass::TileClass()
{
	m_Highlight = false;
	m_HighlighterSprite = 0;
}


TileClass::TileClass(const TileClass& other)
{
}


TileClass::~TileClass()
{
}


void TileClass::Shutdown()
{
	if(m_HighlighterSprite)
	{
		m_HighlighterSprite->Shutdown();
		delete m_HighlighterSprite;
		m_HighlighterSprite = 0;
	}
	SpriteClass::Shutdown();
}


int TileClass::GetTypeId()
{
	return m_TypeId;
}


void TileClass::SetTypeId(int id)
{
	m_TypeId = id;
}


void TileClass::SetHighlight(bool state)
{
	if(state == false && m_Highlight == true)
	{
		if(m_HighlighterSprite)
		{
			m_HighlighterSprite->Shutdown();
			delete m_HighlighterSprite;
			m_HighlighterSprite = 0;
		}
	}
	m_Highlight = state;
}


bool TileClass::Render(ID3D10Device* device, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX orthoMatrix, unsigned int screenWidth, unsigned int screenHeight)
{
	bool result = true;

	result = SpriteClass::Render(device, worldMatrix, viewMatrix, orthoMatrix, screenWidth, screenHeight);
	if(!result)
	{
		return false;
	}

	//if(m_Highlight)
	//{
	//	if(!m_HighlighterSprite)
	//	{
	//		m_HighlighterSprite = new SpriteClass;
	//		result = m_HighlighterSprite->Initialise(device, SpriteClass::GetTexture(), SpriteClass::GetTextureShader());
	//		if(!result)
	//		{
	//			return false;
	//		}
	//		m_HighlighterSprite->SetTextureId(SPRITE_TEX_HIGHLIGHT);
	//	}
	//	m_HighlighterSprite->SetPosition(SpriteClass::GetPositionX(), SpriteClass::GetPositionX());
	//	m_HighlighterSprite->Render(device, worldMatrix, viewMatrix, orthoMatrix, screenWidth, screenHeight);
	//}

	return true;
}
