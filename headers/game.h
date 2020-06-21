#include "functions.h"
#include "map.h"
#include "screen.h"
#include "input.h"
#include "config.h"
#include "control.h"


class Game {
	public:
		Game();
		~Game();

		void start();
		bool isTryAgain();

	private:
		Map *map;
		Screen *screen;
		Input *input;
		Functions *functions;
		Config *config;
        Control *control;

        void initNewGame();

        void doControl();

		bool isexit;
		bool istryagain;

		void exit();
		void restart();
		void finish();

		void exitQuestion();

};
