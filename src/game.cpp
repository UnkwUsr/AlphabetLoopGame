#include "game.h"



Game::Game()
{
	screen = new Screen();
	input = new Input();

	map = new Map();

	config = new Config();
	functions = new Functions(screen, input, config, map);

    map->Init();
}

Game::~Game()
{
	delete functions;
	delete screen;
	delete input;
	delete config;
	delete map;
}

// TODO: некоторые функции из Functions нужно вынести сюда.
// грубо говоря, оно должна работать(EDITED: НЕ ДОЛЖНО!!!!!!!!!!!!!!!!!! для каждого экземляра игры - свой объект Game) так, чтобы я мог в любой момент создать второй экземляр игры,
// и всё работало c минимальной нагрузкой (ведь функции из Functions можно использовать во всех экземлярах игры)
void Game::start()
{
	functions->initNewGame();

	while(!functions->isexit)
	{
		screen->draw(map);

		functions->doControl();
	}
}

bool Game::isTryAgain()
{
	return functions->istryagain;
}
