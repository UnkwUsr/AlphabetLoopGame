#include "game.h"

#include <fstream>
#include <string.h>
std::ofstream logfile;


int main(int argc, char* argv[])
{
    if(argc >= 2 && strcmp(argv[1], "--debug") == 0)
    {
        logfile = std::ofstream("game.log");
        logfile << "Logging started" << std::endl;
    }

	Game* gameInstance = new Game();

	do {
		gameInstance->start();
	} while(gameInstance->isTryAgain());

	delete gameInstance;

    logfile.close();

	return 0;
}
