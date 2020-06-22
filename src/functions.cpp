#include "functions.h"
#include "common.h"

#include <fstream>


Functions::Functions(Screen* scr, Input* inp, Map* mp) : screen(scr), input(inp), map(mp)
{
    timer = new Timer();
}

Functions::~Functions()
{
}

void Functions::onNewGame()
{
    timer->reset();
}

void Functions::onFrame()
{
    if(!timer->isPaused())
        drawTimer();
}

bool Functions::resolveAction(std::string act)
{
    if(act == "set_highlighting")
    {
        changeHighLightingLetters();
        return true;
    }
    else if(act == "see_completed_map")
    {
        seeCompletedMap();
        return true;
    }
    else
        return false;
}

void Functions::changeHighLightingLetters()
{
	timer->pause();

	screen->drawDialogChangeHightLightingLetters();
	std::string buff = screen->highlightingletters;

	for(char key = input->getKey(); key != '\n'; key = input->getKey())
	{
		if(input->isKEY_BACKSPACE(key))
		{
			if(buff.length() != 0)
			{
				buff.pop_back();
				screen->eraseSymbol();
			}
		}
		else if((int)key >= int('a') && (int)key <= int('y'))
		{
			screen->printSymbol(char(key));
			buff += char(key);
		}
	}

	screen->highlightingletters = buff;

	timer->continu();
}

void Functions::seeCompletedMap()
{
	timer->pause();

	std::string original_mapstr = map->mapstr;
	map->mapstr = map->solvedmapstr;

	screen->drawCompletedMap(map);
	input->getKey();

	map->mapstr = original_mapstr;

	timer->continu();
}

std::string Functions::getTimerTime()
{
    return timer->getDifferentStringify();
}

void Functions::drawTimer()
{
    std::string time = getTimerTime();
    screen->drawTimer(time);
}

void Functions::writeRecordInFile(std::string time, unsigned int amountscrolls)
{
	if(RECORDS_FILENAME != "")
	{
		std::ofstream recordsfile(RECORDS_FILENAME, std::ios_base::app);

		recordsfile << "Time: " << time << "\nAmount scrolls: " << amountscrolls << "\n\n";

		recordsfile.close();
	}
}

