#include "game.h"


int main(int argc, char* argv[])
{
	Game* gameInstance = new Game();

	do {
		gameInstance->start();
	} while(gameInstance->isTryAgain());

	delete gameInstance;

	return 0;
}
