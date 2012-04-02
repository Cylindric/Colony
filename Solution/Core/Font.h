#pragma once

#include <fstream>
#include <iostream>
#include "StandardRenderer.h"
#include "VertexTypes.h"


namespace Core
{
	class Font
	{
	private:

		struct FontType
		{
			float left;
			float right;
			int size;
		};

	public:
		Font(void);
		~Font(void);

		bool Initialise(char* fontFilename, StandardRenderer::TEXTURE_ID textureId);
		void Release(void);

	private:
		int m_TextureId;
		FontType* m_Font;

	private:
		bool LoadFontData(char* fontFilename);

	};
}