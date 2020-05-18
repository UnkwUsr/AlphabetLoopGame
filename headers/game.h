#include "functions.h"
#include "map.h"
#include "screen.h"
#include "input.h"
#include "config.h"


class Game {
	public:
		Game();
		~Game();

		void start();
		bool isTryAgain();

		void drawMap();
	private:
		Map *map;
		Screen *screen;
		Input *input;
		Functions *functions;
		Config *config;
};
