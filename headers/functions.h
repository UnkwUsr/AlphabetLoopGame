#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "screen.h"
#include "input.h"
#include "map.h"

#include "functions/timer.h"


class Functions {
	public:
		Functions(Screen* scr, Input* inp, Map* mp);
		~Functions();

        void onNewGame();
        void onFrame();
        bool resolveAction(std::string act);

        std::string getTimerTime();

        void writeRecordInFile(std::string time, unsigned int amountscrolls);

	private:
		Screen* screen;
		Input* input;
		Map* map;

        Timer* timer;

		void changeHighLightingLetters();
		void seeCompletedMap();

        void drawTimer();
};

#endif
