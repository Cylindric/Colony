#include "Font.h"

using std::ifstream;
using std::cerr;
using std::endl;

namespace Core
{

	Font::Font()
	{
		m_TextureId = 0;
		m_Font = NULL;
	}


	Font::~Font()
	{
	}


	bool Font::Initialise(char* fontFilename, StandardRenderer::TEXTURE_ID textureId)
	{
		bool result = true;
		return true;
	}


	void Font::Release()
	{
		delete [] m_Font;
		m_Font = NULL;
	}


	bool Font::LoadFontData(char* fontFilename)
	{
		ifstream fin;
		int i;
		char temp;

		// create a buffer for the font-spacing information
		m_Font = new FontType[95];

		// read the font-spacing information from the specified font-file
		fin.open(fontFilename);
		if(fin.fail())
		{
			cerr << "Failed to load font data " << fontFilename << endl;
			return false;
		}

		// read in the font spacing data
		for(i = 0; i < 95; i++)
		{
			fin.get(temp);
			while(temp != ' ')
			{
				fin.get(temp);
			}
			fin.get(temp);
			while(temp != ' ')
			{
				fin.get(temp);
			}
			fin >> m_Font[i].left;
			fin >> m_Font[i].right;
			fin >> m_Font[i].size;
		}

		fin.close();

		return true;
	}

}