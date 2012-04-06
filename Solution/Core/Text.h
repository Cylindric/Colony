#pragma once


//////////////
// INCLUDES //
//////////////
#include <map>
#include <string>
#include <vector>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "global.h"
#include "Font.h"
#include "VertexTypes.h"


namespace Core
{
	class Text
	{
	public:

		struct Sentence
		{
			std::string text;
			int position[2];
			float fontSize;
		};

		Text(void);
		~Text(void);

		// pipeline methods
		bool Initialise(Font* font);
		void Release(void);
		bool Update(void);
		std::vector<SpriteVertex>* GetSprites(void);

		// class methods
		int InitialiseSentence(void);
		bool UpdateSentence(int id, std::string text, int posX = -1, int posY = -1, float fontSize = -1);
		bool UpdateSentence(int id, char* text, int value);
		//void ReleaseSentence(int id);

	private:
		Font* m_Font;
		std::map<int, Sentence> m_Strings;
		std::vector<SpriteVertex> m_Chars;

	};
}