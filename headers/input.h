#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <map>


class Input {
	public:
		Input();

		char getKey();

		bool isKEY_BACKSPACE(char key);
};

#endif