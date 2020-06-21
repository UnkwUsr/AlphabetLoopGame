#include "functions.h"
#include "common.h"

#include <fstream>


Functions::Functions(Screen* scr, Input* inp, Config* cnfg, Map* mp) : screen(scr), input(inp), config(cnfg), map(mp)
{
}

Functions::~Functions()
{
	saveConfig();
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


void Functions::writeRecordInFile(std::string time, unsigned int amountscrolls)
{
	if(RECORDS_FILENAME != "")
	{
		std::ofstream recordsfile(RECORDS_FILENAME, std::ios_base::app);

		recordsfile << "Time: " << time << "\nAmount scrolls: " << amountscrolls << "\n\n";

		recordsfile.close();
	}
}




void Functions::saveConfig()
{
	// TODO: если config.cfg не обнаржуен, то нужно самому создавать его, и записывать стандартные настройки + управление для карты 5x5 (то есть квары и бинды)
	// // if(saveconfig)
	// std::ofstream configfile(config->FILENAME);

	// for(auto &item : cvars_list)
	// {
	// 	std::string name = item.first;
	// 	configfile << name << " ";

	// 	cvar cvr = item.second;
	// 	if(cvr.type == CVAR_INT)
	// 	{
	// 		int* int_ptr = static_cast<int*>(cvr.ptr);
	// 		configfile << *int_ptr;
	// 	}
	// 	else if(cvr.type == CVAR_STR)
	// 	{
	// 		std::string* string_ptr = static_cast<std::string*>(cvr.ptr);
	// 		configfile << *string_ptr;
	// 	}
	// 	else if(cvr.type == CVAR_BOOL)
	// 	{
	// 		bool* string_ptr = static_cast<bool*>(cvr.ptr);
	// 		configfile << *string_ptr;
	// 	}
	// 	configfile << std::endl;
	// }

	// configfile.close();
}
