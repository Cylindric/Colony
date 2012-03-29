////////////////////////////////////////////////////////////////////////////////
// Filename: textclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTCLASS_H_
#define _TEXTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <iostream>
#include <map>
#include <assert.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "FontClass.h"
#include "FontShaderClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: TextClass
////////////////////////////////////////////////////////////////////////////////
class TextClass
{
private:

	struct SentenceType
	{
		ID3D10Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialise(ID3D10Device*, HWND, int, int, D3DXMATRIX);
	void Shutdown();
	void Render(ID3D10Device*, D3DXMATRIX, D3DXMATRIX);
	bool SetFps(int fps);
	bool SetMousePosition(int mouseX, int mouseY);

private:
	int InitialiseSentence(int sentenceId, ID3D10Device*);
	bool UpdateSentence(int sentenceId, char*, int, int, float, float, float);
	void RenderSentence(ID3D10Device*, int sentenceId, D3DXMATRIX, D3DXMATRIX);

private:
	bool m_Shutdown;
	FontClass* m_Font;
	FontShaderClass* m_FontShader;
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;

	// sentences
	std::map<int, SentenceType*> m_Sentences;
	int m_FpsSentence;
	int m_MouseSentence;

};

#endif
