#include "Text.h"

using std::ifstream;
using std::string;
using std::pair;

namespace Core
{

	Text::Text()
	{
		m_Font = NULL;
	}


	Text::~Text()
	{
	}


	std::vector<SpriteVertex>* Text::GetSprites()
	{
		return &m_Chars;
	}


	bool Text::Initialise(Font* font)
	{
		m_Font = font;
		return true;
	}


	void Text::Release()
	{
		m_Chars.clear();
		m_Font = NULL;
	}


	int Text::InitialiseSentence()
	{
		int id = m_Strings.size();
		Sentence s = {"", 0, 0, 1.0f};
		m_Strings.insert(std::pair<int, Sentence>(id, s));
		return id;
	}


	bool Text::UpdateSentence(int id, std::string text, int posX, int posY, float size)
	{
		m_Strings[id].position[0] = posX;
		m_Strings[id].position[1] = posY;
		m_Strings[id].text = text;
		m_Strings[id].size = size;
		return true;
	}


	bool Text::Update()
	{
		int chars;
		int letter;
		SpriteVertex v;
		Font::FontType f;

		float pxToClipWidth = convertPixelsToClipSpaceDistance(800, 1);
		float pxToClipHeight = convertPixelsToClipSpaceDistance(600, 1);
		float wordSpace = 5 * pxToClipWidth;
		float charSpace = 1 * pxToClipWidth;
		float letterClipWidth = 0.0f;
		float letterClipHeight = 0.0f;

		m_Chars.clear();

		for(auto it = m_Strings.begin(); it != m_Strings.end(); ++it)
		{
			letterClipHeight = 16 * pxToClipHeight * ((*it).second.size);

			v.spriteType = SPRITE_TYPE_TEXT;
			v.topLeft[0] = convertPixelsToClipSpace(800, (*it).second.position[0]);
			v.topLeft[1] = convertPixelsToClipSpace(600, (*it).second.position[1]);
			v.opacity = 1.0f;
			v.uvTop = 0;
			v.uvBottom = 1;

			chars = (*it).second.text.length();
			for(int i = 0; i < chars; i++)
			{
				letter = ((int)(*it).second.text[i]) - 32;

				if(letter == 0)
				{
					v.topLeft[0] += wordSpace * ((*it).second.size);
				} 
				else
				{
					f = m_Font->GetCharDetails(letter);
					letterClipWidth = pxToClipWidth * f.size * ((*it).second.size);

					v.uvLeft = f.left;
					v.uvRight = f.right;
					v.dimensions[0] = letterClipWidth;
					v.dimensions[1] = letterClipHeight;

					// add the character to the list
					m_Chars.push_back(v);

					// increment horizontal position
					v.topLeft[0] += (v.dimensions[0] + charSpace);
				}

			}
			
		}
		return true;
	}

}