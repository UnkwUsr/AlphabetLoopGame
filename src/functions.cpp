#include "functions.h"
#include "common.h"

#include <fstream>
#include <unordered_map>



Functions::Functions(Screen* scr, Input* inp, Config* cnfg, Map* mp) : screen(scr), input(inp), config(cnfg), map(mp)
{
	initFunctions();
	config->readConfig();
}

Functions::~Functions()
{
	saveConfig();
}

void Functions::initFunctions()
{
	initFunc("exit", &Functions::exit, 'q');
	initFunc("restart", &Functions::restart, 'r');

	initFunc("set_highlighting", &Functions::changeHighLightingLetters, 0);
	initFunc("see_completed_map", &Functions::seeCompletedMap, 0);
	initFunc("undo_scroll", &Functions::undoScroll, 0);
}

void Functions::initFunc(std::string name, action_func func, char key)
{
	actions[name] = func;

	// if(USE_DEFAULT_BINDS && key != 0)
		config->bindKey(key, name);
}


void Functions::initNewGame()
{
	isexit = false;
	istryagain = false;
	amountscrolls = 0;
	timer = new Timer();
	srand(time(NULL));

	map->reset();
	initScrollFuncs();

	randomizeMap();
	scrolls_history.clear();
}

void Functions::initScrollFuncs()
{
	const std::string SCROLL = "scroll_";

	actions_scrolls.clear();
	for(unsigned int i = 0; i < HORIZ_LEN; ++i)
	{
		actions_scrolls[SCROLL + "up_" + std::to_string(i)] = {DIR_UP, i};
		actions_scrolls[SCROLL + "down_" + std::to_string(i)] = {DIR_DOWN, i};
	}
	for(unsigned int i = 0; i < VERT_LEN; ++i)
	{
		actions_scrolls[SCROLL + "left_" + std::to_string(i)] = {DIR_LEFT, i};
		actions_scrolls[SCROLL + "right_" + std::to_string(i)] = {DIR_RIGHT, i};
	}
}


void Functions::doControl()
{
	std::string act = config->getActionByKey(input->getKey());
	if(act == config->ACTION_NULL)
		return;

	auto it = actions.find(act);
	if(it != actions.end())
	{
		action_func func = it->second;
		(this->*func)();
	}
	else
	{
		auto it = actions_scrolls.find(act);
		if(it != actions_scrolls.end())
		{
			scroll_arg scroll = it->second;

			bool temp = false; // TOOD: пофиксить вот это, ибо пришлось наговнокодить
			if(AUTO_UNDO_SAME_SCROLLS && !scrolls_history.empty())
			{
				scroll_arg lastscroll = scrolls_history.back();
				if(scroll.num == lastscroll.num && scroll.dir == lastscroll.dir * -1)
				{
					undoScroll();
					temp = true;
				}
			}
			if(!temp)
			{
				scrolls_history.push_back(scroll);
				doScroll(scroll.dir, scroll.num);
				amountscrolls++;
			}

			checkComplete();
		}
		else
		{
			// console->printError("Unknown command: " + act);
			// TODO: дописать. EDITED: можно написать типа консоль, и вот туда я тогда буду выводить эту ошибку
		}
	}
}


void Functions::doScroll(int dir, unsigned int num)
{
	if(dir == DIR_LEFT)
		map->scrollLeft(num);
	else if(dir == DIR_RIGHT)
		map->scrollRight(num);
	else if(dir == DIR_UP)
		map->scrollUp(num);
	else if(dir == DIR_DOWN)
		map->scrollDown(num);
}


void Functions::randomizeMap()
{
	if(RANDOMIZE_MAP)
	{
		unsigned int rnd_steps = MIN_RAND_STEPS + rand() % MAX_RAND_STEPS;
		for(unsigned int i = 0; i < rnd_steps; ++i)
		{
			unsigned int rnd_num = 0;
			int rnd_dir = DIR_LEFT + rand() % DIR_DOWN;

			if(rnd_dir == DIR_LEFT || rnd_dir == DIR_RIGHT)
				rnd_num = 0 + rand() % VERT_LEN;
			else if(rnd_dir == DIR_UP || rnd_dir == DIR_DOWN)
				rnd_num = 0 + rand() % HORIZ_LEN;

			doScroll(rnd_dir, rnd_num);
		}
	}
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


void Functions::exitQuestion()
{
	if(input->getKey() == 'q')
		isexit = true;
}

void Functions::exit()
{
	screen->printString("If you really want to quit, then press 'q' again.\n", true);
	screen->printString("If no - press any other key.", false, true);

	exitQuestion();
}

void Functions::restart()
{
	screen->printString("If you really want restart the game, then press 'r' again.\n", true);
	screen->printString("If no - press any other key.", false, true);

	if(input->getKey() == 'r')
	{
		isexit = true;
		istryagain = true;
	}
}


void Functions::checkComplete()
{
	if(map->isCompleted())
		finish();
}

void Functions::finish()
{
	std::string time = timer->getDifferentStringify();
	delete timer;

	writeRecordInFile(time, amountscrolls);
	screen->printString("YOU WIN!!!\n\n", true);

	screen->printString(("Your time: " + time + ".\n").c_str());
	screen->printString(("Number of scrolls: " + std::to_string(amountscrolls) + ".\n\n").c_str());

	screen->printString("Press 'q' to quit the game.\n");
	screen->printString("Press any other key to play again.", false, true);


	exitQuestion();
	if(!isexit)
	{
		isexit = true;
		istryagain = true;
	}
}

inline void Functions::writeRecordInFile(std::string time, unsigned int amountscrolls)
{
	if(RECORDS_FILENAME != "")
	{
		std::ofstream recordsfile(RECORDS_FILENAME, std::ios_base::app);

		recordsfile << "Time: " << time << "\nAmount scrolls: " << amountscrolls << "\n\n";

		recordsfile.close();
	}
}


void Functions::undoScroll()
{
	if(!scrolls_history.empty())
	{
		scroll_arg lastscroll = scrolls_history.back();
		scrolls_history.pop_back();

		lastscroll.dir *= -1;
		doScroll(lastscroll.dir, lastscroll.num);

		amountscrolls--;
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
