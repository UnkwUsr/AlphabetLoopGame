#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "screen.h"
#include "input.h"
#include "map.h"
#include "config.h"

#include "functions/timer.h"

#include <map>
#include <vector>


class Functions {
	public:
		Functions(Screen* scr, Input* inp, Config* cnfg, Map* mp);
		~Functions();

		void initNewGame();

		bool isexit;
		bool istryagain;

		void doControl();
	private:
		Screen* screen;
		Input* input;
		Config* config;
		Map* map;

		Timer* timer;


		void saveConfig();

		void initFunctions();
		void initScrollFuncs();

		void randomizeMap();


		typedef void (Functions::* action_func)();
		std::map<std::string, action_func> actions;
		void initFunc(std::string name, action_func func, char key);
		// const bool USE_DEFAULT_BINDS = true;

		enum {DIR_LEFT = 1, DIR_RIGHT = -1, DIR_UP = 2, DIR_DOWN = -2};
		struct scroll_arg {
			int dir;
			unsigned int num;
		};
		std::map<std::string, scroll_arg> actions_scrolls;
		void doScroll(int dir, unsigned int num);
		unsigned int amountscrolls;


		void exit();
		void restart();
		void changeHighLightingLetters();
		void seeCompletedMap();

		void undoScroll();
		std::vector<scroll_arg> scrolls_history;


		void exitQuestion();
		void checkComplete();

		void finish();
		inline void writeRecordInFile(std::string time, unsigned int amountscrolls);
};

#endif