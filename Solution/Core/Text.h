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
		static const unsigned int MAX_SENTENCE_LENGTH = 128;

		struct Sentence
		{
			std::string text;
			int position[2];
			float fontSize;
		};

		Text(void);
		~Text(void);
		void SetSentencePosition(int id, int x, int y);

		// pipeline methods
		bool Initialise(Font* font);
		void Release(void);
		bool Update(void);
		std::vector<SpriteVertex>* GetSprites(void);

		// class methods
		int InitialiseSentence(char* text = "", int posX = 0, int posY = 0, float fontSize = 1.0f);
		bool UpdateSentence(int id, char* format, ...);
		//void ReleaseSentence(int id);

	private:
		Font* m_Font;
		std::map<int, Sentence> m_Strings;
		std::vector<SpriteVertex> m_Chars;

	};
}