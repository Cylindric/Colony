///////////////////////////////////////////////////////////////////////////////
// Filename: TextClass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "TextClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: TextClass
////////////////////////////////////////////////////////////////////////////////
TextClass::TextClass()
{
	m_Font = 0;
	m_FontShader = 0;
	m_MouseSentence = 0;
	m_FpsSentence = 0;
	m_Shutdown = false;
}


TextClass::TextClass(const TextClass& other)
{
}


TextClass::~TextClass()
{
	if(!m_Shutdown)
	{
		std::cerr << "Text not shut down before destruction" << std::endl;
	}
	assert(m_Shutdown);
}


bool TextClass::Initialise(ID3D10Device* device, HWND hwnd, int screenWidth, int screenHeight, D3DXMATRIX baseViewMatrix)
{
	bool result;

	// Store the screen width and height.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the base view matrix.
	m_baseViewMatrix = baseViewMatrix;

	// Create the font object.
	m_Font = new FontClass;
	if(!m_Font)
	{
		return false;
	}

	// Initialise the font object.
	result = m_Font->Initialise(device, "./fonts/default.txt", L"./fonts/default.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the font object.", L"Error", MB_OK);
		return false;
	}

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialise the font shader object.
	result = m_FontShader->Initialise(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialise the font shader object.", L"Error", MB_OK);
		return false;
	}


	// Initialise the sentences.
	m_FpsSentence = InitialiseSentence(16, device);
	m_MouseSentence = InitialiseSentence(16, device);

	result = UpdateSentence(m_FpsSentence, "Hello", 100, 100, 1.0f, 1.0f, 1.0f);
	result = UpdateSentence(m_MouseSentence, "Goodbye", 100, 200, 1.0f, 1.0f, 0.0f);

	return true;
}


void TextClass::Shutdown()
{
	// Release the sentences.
	for(std::map<int, SentenceType*>::iterator it = m_Sentences.begin(); it != m_Sentences.end();)
	{
		// Release the sentence vertex buffer.
		if(it->second->vertexBuffer)
		{
			it->second->vertexBuffer->Release();
			it->second->vertexBuffer = 0;
		}

		// Release the sentence index buffer.
		if(it->second->indexBuffer)
		{
			it->second->indexBuffer->Release();
			it->second->indexBuffer = 0;
		}

		// Release the sentence.
		it = m_Sentences.erase(it);
	}

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the font object.
	if(m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	m_Shutdown = true;
}


void TextClass::Render(ID3D10Device* device, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	for(std::map<int, SentenceType*>::iterator s = m_Sentences.begin(); s != m_Sentences.end(); s++)
	{
		RenderSentence(device, s->first, worldMatrix, orthoMatrix);
	}
}


int TextClass::InitialiseSentence(int maxLength, ID3D10Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	// Create a new sentence object.
	SentenceType* sentence = new SentenceType;

	// Initialise the sentence buffers to null.
	sentence->vertexBuffer = 0;
	sentence->indexBuffer = 0;

	// Set the maximum length of the sentence.
	sentence->maxLength = maxLength;

	// Set the number of vertices in the vertex array.
	sentence->vertexCount = 6 * maxLength;

	// Set the number of indexes in the index array.
	sentence->indexCount = sentence->vertexCount;

	// Create the vertex array.
	vertices = new VertexType[sentence->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[sentence->indexCount];
	if(!indices)
	{
		return false;
	}

	// Initialise vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	// Initialise the index array.
	for(i=0; i<sentence->indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * sentence->vertexCount;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;

	// Create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &sentence->vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * sentence->indexCount;
	indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &sentence->indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	// Release the index array as it is no longer needed.
	delete [] indices;
	indices = 0;

	int key = m_Sentences.size();
	m_Sentences.insert(std::pair<int, SentenceType*>(key, sentence));

	return key;
}


bool TextClass::SetFps(int fps)
{
	char tempString[16];
	char fpsString[16];
	float red, green, blue;
	bool result;

	// Truncate the fps
	if(fps > 9999)
	{
		fps = 9999;
	}

	// Convert the FPS to a string
	_itoa_s(fps, tempString, 10);

	// Setup the string
	strcpy_s(fpsString, "FPS: ");
	strcat_s(fpsString, tempString);

	// Colour the text by rate
	if(fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
	}
	if(fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}
	if(fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}

	// Update the sentence buffer
	result = UpdateSentence(m_FpsSentence, fpsString, 10, 10, red, green, blue);
	if(!result)
	{
		return false;
	}

	return true;
}


bool TextClass::SetMousePosition(int mouseX, int mouseY)
{
	char tempString[16];
	char mouseString[16];
	bool result;

	// Convert the mouseX integer to string format.
	_itoa_s(mouseX, tempString, 10);
	strcpy_s(mouseString, "X:");
	strcat_s(mouseString, tempString);

	_itoa_s(mouseY, tempString, 10);
	strcat_s(mouseString, " Y:");
	strcat_s(mouseString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_MouseSentence, mouseString, 10, 26, 1.0f, 1.0f, 1.0f);
	if(!result)
	{
		return false;
	}

	return true;
}


bool TextClass::UpdateSentence(int sentenceId, char* text, int positionX, int positionY, float red, float green, float blue)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	void* verticesPtr;
	HRESULT result;

	std::map<int, SentenceType*>::iterator it = m_Sentences.find(sentenceId);
	SentenceType* sentence = it->second;

	// the color of the sentence.
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(text);

	// Check for possible buffer overflow.
	if(numLetters > sentence->maxLength)
	{
		return false;
	}

	// Create the vertex array.
	vertices = new VertexType[sentence->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Initialise vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	// Calculate the X and Y pixel position on the screen to start drawing to.
	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);

	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

	// Initialise the vertex buffer pointer to null first.
	verticesPtr = 0;

	// Lock the vertex buffer.
	result = sentence->vertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr);
	if(FAILED(result))
	{
		return false;
	}

	// Copy the vertex array into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	// Unlock the vertex buffer.
	sentence->vertexBuffer->Unmap();

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	return true;
}


void TextClass::RenderSentence(ID3D10Device* device, int sentenceId, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	D3DXVECTOR4 pixelColor;

	std::map<int, SentenceType*>::iterator it = m_Sentences.find(sentenceId);
	SentenceType* sentence = it->second;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	device->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	device->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create a pixel color vector with the input sentence color.
	pixelColor = D3DXVECTOR4(sentence->red, sentence->green, sentence->blue, 1.0f);

	// Render the text using the font shader.
	m_FontShader->Render(device, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(), pixelColor);

	return;
}
