#include "screen.h"
#include "common.h"

#include <ncurses.h>



Screen::Screen()
{
	initscr();
	keypad(stdscr, true);
	noecho();

	highlightingletters = "";
}

Screen::~Screen()
{
	endwin();
}

void Screen::predraw()
{
	clear();
	move(0, 0);
}

void Screen::draw(Map* map)
{
	predraw();

	getmaxyx(stdscr, row, col);

	drawMap(map);
	mvprintw(row - 1, 0, "Press 'q' for exit.");

	refresh();
}

void Screen::drawMap(Map* map)
{
	for(unsigned int i = 0, posi = i + VERT_INDENT; i < VERT_LEN; ++i, posi += BLOCK_SIZE)
	{
		std::string rowstr = map->getRow(i);
		for(unsigned int j = 0, posj = j + HORIZ_INDENT; j < HORIZ_LEN; ++j, posj += BLOCK_SIZE)
		{
			std::string letter = std::string(1, rowstr[j]);

			int starty = posi + VERT_SPACES_NUM * i;
			int startx = posj + HORIZ_SPACES_NUM * j;

			if(highlightingletters.find(letter) != std::string::npos)
			{
				attrset(A_STANDOUT);

				drawBlockLetter(starty, startx, letter);

				standend();
			}
			else
				drawBlockLetter(starty, startx, letter);
		}
	}
}

void Screen::drawBlockLetter(int starty, int startx, std::string letter)
{
	int endy = starty + BLOCK_SIZE;
	int endx = startx + BLOCK_SIZE;

	for(int i = starty; i < endy; i++)
	{
		move(i, startx);
		for(int j = startx; j < endx; j++)
			printw(letter.c_str());
	}
}


void Screen::printString(const char* str, bool isfirstframe, bool islastframe, int y, int x)
{
	if(isfirstframe)
		predraw();

	if(y == -1 && x == -1)
		printw(str);
	else
		mvprintw(y, x, str);

	if(islastframe)
		refresh();
}
// TODO: может ещеё написать функцию для получения currentY и X
// P.S. впринципе если ещё написать эту функцию, то наверное можно будет drawMap перенести в functions


void Screen::drawDialogChangeHightLightingLetters()
{
	predraw();

	printw("Enter string with letters who you want to highlighting:\n");
	printw(highlightingletters.c_str());

	refresh();
}

void Screen::drawCompletedMap(Map* map)
{
	predraw();

	drawMap(map);

	mvprintw(row - 1, 0, "Is completed map, press any key for return to game.");
}



void Screen::eraseSymbol()
{
	int y, x;
	getyx(stdscr, y, x);

	move(y, x - 1);
	printw(" ");
	move(y, x - 1);

	refresh();
}

void Screen::printSymbol(char a)
{
	printw(&a);
}