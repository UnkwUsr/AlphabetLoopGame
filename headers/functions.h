#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "screen.h"
#include "input.h"
#include "map.h"
#include "config.h"

#include "functions/timer.h"


class Functions {
	public:
		Functions(Screen* scr, Input* inp, Config* cnfg, Map* mp);
		~Functions();

        bool resolveAction(std::string act);

        Timer* timer;

	private:
		Screen* screen;
		Input* input;
		Config* config;
		Map* map;


		void saveConfig();

		void changeHighLightingLetters();
		void seeCompletedMap();

		void writeRecordInFile(std::string time, unsigned int amountscrolls);
};

#endif
