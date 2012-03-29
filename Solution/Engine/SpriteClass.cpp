////////////////////////////////////////////////////////////////////////////////
// Filename: SpriteClass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SpriteClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: SpriteClass
////////////////////////////////////////////////////////////////////////////////
SpriteClass::SpriteClass()
{
	m_VertexBuffer = 0;
	m_IndexBuffer = 0;
	m_Texture = 0;
	m_PosX = 0;
	m_PosY = 0;
	m_PreviousPosX = -1;
	m_PreviousPosY = -1;
	m_Shutdown = false;
}


SpriteClass::SpriteClass(const SpriteClass& other)
{
}


SpriteClass::~SpriteClass()
{
	if(!m_Shutdown)
	{
		std::cerr << "Sprite not shut down before destruction" << std::endl;
	}
	assert(m_Shutdown);
}


bool SpriteClass::Initialise(ID3D10Device* device, TextureClass* texture, TextureShaderClass* textureShader)
{
	bool result;

	// Initialise the previous rendering position to negative one.
	m_PreviousPosX = -1;
	m_PreviousPosY = -1;

	// Initialise the vertex and index buffer that hold the geometry for the triangle.
	result = InitialiseBuffers(device);
	if(!result)
	{
		return false;
	}

	// Set the texture and shader for this model.
	if(!texture)
	{
		return false;
	}
	m_Texture = texture;

	if(!textureShader)
	{
		return false;
	}
	m_TextureShader = textureShader;

	return true;
}


void SpriteClass::Shutdown()
{
	ShutdownBuffers();
	m_Shutdown = true;
}


bool SpriteClass::Render(ID3D10Device* device, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX orthoMatrix, unsigned int screenWidth, unsigned int screenHeight)
{
	bool result;

	// Re-build the dynamic vertex buffer for rendering to possibly a different location on the screen.
	result = UpdateBuffers(screenWidth, screenHeight);
	if(!result)
	{
		return false;
	}

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(device);

	m_TextureShader->Render(device, m_IndexCount, worldMatrix, viewMatrix, orthoMatrix, m_Texture->GetTexture());

	return true;
}


int SpriteClass::GetIndexCount()
{
	return m_IndexCount;
}


void SpriteClass::SetTextureId(SpriteTexId id)
{
	m_TextureId = id;
}


void SpriteClass::SetPosition(int x, int y)
{
	m_PosX = x;
	m_PosY = y;
}


int SpriteClass::GetPositionX()
{
	return m_PosX;
}


int SpriteClass::GetPositionY()
{
	return m_PosY;
}


TextureClass* SpriteClass::GetTexture()
{
	return m_Texture;
}


TextureShaderClass* SpriteClass::GetTextureShader()
{
	return m_TextureShader;
}


bool SpriteClass::InitialiseBuffers(ID3D10Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D10_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Set the number of vertices in the vertex array.
	m_VertexCount = 6;

	// Set the number of indices in the index array.
	m_IndexCount = m_VertexCount;

	// Create the vertex array.
	vertices = new VertexType[m_VertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_IndexCount];
	if(!indices)
	{
		return false;
	}

	// Initialise vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * m_VertexCount));

	// Load the index array with data.
	for(i=0; i<m_IndexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
    vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_VertexCount;
    vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;

	// Now finally create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the index buffer.
    indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_IndexCount;
    indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void SpriteClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_IndexBuffer)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = 0;
	}

	return;
}


bool SpriteClass::UpdateBuffers(unsigned int screenWidth, unsigned int screenHeight)
{
	float left = 0;
	float right = 0;
	float top = 0;
	float bottom = 0;
	VertexType* vertices;
	void* verticesPtr;
	HRESULT result;

	// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
	// currently has the correct parameters.
	if((m_PosX == m_PreviousPosX) && (m_PosY == m_PreviousPosY))
	{
		return true;
	}
	
	// If it has changed then update the position it is being rendered to.
	m_PreviousPosX = m_PosX;
	m_PreviousPosY = m_PosY;

	// Calculate the screen coordinates of the left side of the bitmap.
	left = ((float)(screenWidth / 2) * -1) + ((float)m_PosX * SPRITE_SIZE);

	// Calculate the screen coordinates of the right side of the bitmap.
	right = left + (float)SPRITE_SIZE;

	// Calculate the screen coordinates of the top of the bitmap.
	top = (float)(screenHeight / 2) - ((float)m_PosY * SPRITE_SIZE);

	// Calculate the screen coordinates of the bottom of the bitmap.
	bottom = top - (float)SPRITE_SIZE;

	// Create the vertex array.
	vertices = new VertexType[m_VertexCount];
	if(!vertices)
	{
		return false;
	}

	float twidth = 16.0/256;
	int textureColumns = 256/16;
	int row = 0;
	int col = 0;
	float u0, u1, u2, u3;
	float v0, v1, v2, v3;
	float j = 0.5/256; // adjust uv's by half a pixel to remove edge-bleed

	row = (m_TextureId / textureColumns);
	col = (m_TextureId % textureColumns);

	u0 = (col * twidth) + j + 0.0f;   v0 = (row * twidth) + j + 0.0f;
	u1 = (col * twidth) - j + twidth; v1 = (row * twidth) - j + twidth;
	u2 = (col * twidth) + j + 0.0f;   v2 = (row * twidth) - j + twidth;
	u3 = (col * twidth) - j + twidth; v3 = (row * twidth) + j + 0.0f;
	
	// Load the vertex array with data.
	// First triangle.
	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[0].texture = D3DXVECTOR2(u0, v0);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[1].texture = D3DXVECTOR2(u1, v1);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);  // Bottom left.
	vertices[2].texture = D3DXVECTOR2(u2, v2);

	// Second triangle.
	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[3].texture = D3DXVECTOR2(u0, v0);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);  // Top right.
	vertices[4].texture = D3DXVECTOR2(u3, v3);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[5].texture = D3DXVECTOR2(u1, v1);

	// Initialise the vertex buffer pointer to null first.
	verticesPtr = 0;

	// Lock the vertex buffer.
	result = m_VertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr);
	if(FAILED(result))
	{
		return false;
	}

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_VertexCount));

	// Unlock the vertex buffer.
	m_VertexBuffer->Unmap();

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	return true;
}


void SpriteClass::RenderBuffers(ID3D10Device* device)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
    stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	device->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    device->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}
