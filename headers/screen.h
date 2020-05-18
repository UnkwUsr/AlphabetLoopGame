#ifndef SCREEN_H
#define SCREEN_H

#include "map.h"
#include <string>


class Screen {
	public:
		Screen();
		~Screen();

		void draw(Map* map);

		void printString(const char* str, bool isfirstframe = false, bool islastframe = false, int y = -1, int x = -1);

		void drawDialogChangeHightLightingLetters();
		std::string highlightingletters;

		void drawCompletedMap(Map* map);


		void printSymbol(char a);
		void eraseSymbol();
	private:
		void predraw();

		void drawMap(Map* map);
		void drawBlockLetter(int starty, int startx, std::string letter);

		int row, col;
};

#endif