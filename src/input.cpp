#include "input.h"

#include <ncurses.h>


Input::Input()
{

}

char Input::getKey()
{
	return (char)getch();
}


bool Input::isKEY_BACKSPACE(char key)
{
	return key == (char)KEY_BACKSPACE;
}
