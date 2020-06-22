#include "game.h"


Game::Game()
{
	screen = new Screen();
	input = new Input();

	map = new Map();

	config = new Config();

	functions = new Functions(screen, input, map);
    control = new Control(map);

    map->Init();

    config->bindKey('q', "exit");
    config->bindKey('r', "restart");
}

Game::~Game()
{
	delete functions;
	delete screen;
	delete input;
	delete config;
	delete map;
	delete control;
}

void Game::initNewGame()
{
    isexit = false;
    istryagain = false;

    functions->onNewGame();

    srand(time(NULL));

    map->reset();
    control->randomizeMap();
    control->scrolls_history.clear();
    control->amountscrolls = 0;
}

void Game::start()
{
	initNewGame();

	while(!isexit)
	{
		screen->draw(map);
        functions->onFrame();

		doControl();

        if(map->isCompleted())
            finish();
	}
}

void Game::doControl()
{
    std::string act = config->getActionByKey(input->getKey());
    if(act == config->ACTION_NULL)
        return;

    /* find who can resolve action */
    if(control->resolveAction(act))
        return;
    if(act == "exit")
    {
        exit();
        return;
    }
    if(act == "restart")
    {
        restart();
        return;
    }
    if(functions->resolveAction(act))
        return;
}

bool Game::isTryAgain()
{
	return istryagain;
}


void Game::exit()
{
    screen->printString("If you really want to quit, then press 'q' again.\n", true);
    screen->printString("If no - press any other key.", false, true);

    exitQuestion();
}

void Game::restart()
{
    screen->printString("If you really want restart the game, then press 'r' again.\n", true);
    screen->printString("If no - press any other key.", false, true);

    if(input->getKey() == 'r')
    {
        isexit = true;
        istryagain = true;
    }
}


void Game::finish()
{
    std::string time = functions->getTimerTime();

    functions->writeRecordInFile(time, control->amountscrolls);
    screen->printString("YOU WIN!!!\n\n", true);

    screen->printString(("Your time: " + time + ".\n").c_str());
    screen->printString(("Number of scrolls: " + std::to_string(control->amountscrolls) + ".\n\n").c_str());

    screen->printString("Press 'q' to quit the game.\n");
    screen->printString("Press any other key to play again.", false, true);


    exitQuestion();
    if(!isexit)
    {
        isexit = true;
        istryagain = true;
    }
}

void Game::exitQuestion()
{
    if(input->getKey() == 'q')
        isexit = true;
}

