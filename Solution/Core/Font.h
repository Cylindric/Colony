#pragma once

#include <vector>
#include <fstream>
#include "global.h"
#include "StandardRenderer.h"
#include "VertexTypes.h"


namespace Core
{
	class Font
	{
	public:

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
		FontType GetCharDetails(int c);

	private:
		int m_TextureId;
		FontType* m_Font;

	private:
		bool LoadFontData(char* fontFilename);

	};
}