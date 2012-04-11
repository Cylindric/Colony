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


	int Text::InitialiseSentence(char* text, int posX, int posY, float fontSize)
	{
		int id = m_Strings.size();
		Sentence s;
		s.text = text;
		s.position[0] = posX;
		s.position[1] = posY;
		s.fontSize = fontSize;
		m_Strings.insert(std::pair<int, Sentence>(id, s));
		return id;
	}


	void Text::SetSentencePosition(int id, int x, int y)
	{
		m_Strings[id].position[0] = x;
		m_Strings[id].position[1] = y;
	}


	bool Text::UpdateSentence(int id, char* format, ...)
	{
		va_list args;
		va_start(args, format);
		char finalString[MAX_SENTENCE_LENGTH];
		vsprintf_s(finalString, sizeof(finalString), format, args);
		m_Strings[id].text = finalString;
		va_end(args);
		return true;
	}


	bool Text::Update()
	{
		int chars;
		int letter;
		SpriteVertex v;
		Font::FontType f;

		float wordSpace = 5;
		float charSpace = 1;

		m_Chars.clear();

		for(auto it = m_Strings.begin(); it != m_Strings.end(); ++it)
		{
			v.spriteType = SPRITE_TYPE_TEXT;
			v.topLeft[0] = (*it).second.position[0];
			v.topLeft[1] = (*it).second.position[1];
			v.opacity = 1.0f;
			v.uvTop = 0;
			v.uvBottom = 1;

			chars = (*it).second.text.length();
			for(int i = 0; i < chars; i++)
			{
				letter = ((int)(*it).second.text[i]) - 32;

				if(letter == 0)
				{
					v.topLeft[0] += (int)(((*it).second.fontSize) * wordSpace);
				} 
				else
				{
					f = m_Font->GetCharDetails(letter);

					v.uvLeft = f.left;
					v.uvRight = f.right;
					v.dimensions[0] = (int)(((*it).second.fontSize) * f.size);
					v.dimensions[1] = 16;

					// add the character to the list
					m_Chars.push_back(v);

					// increment horizontal position
					v.topLeft[0] += (int)(v.dimensions[0] + charSpace);
				}

			}
			
		}
		return true;
	}

}