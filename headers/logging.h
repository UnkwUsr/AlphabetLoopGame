#include <fstream>

extern std::ofstream logfile;

/* How to use:
 * 1. Include logging.h to file where you want use logging
 * 2. Somewhere in your code put line like this:
 * logfile << "Stuff for logging" << std::endl;
 * 3. Run game with argument --debug, like as: ./alphabetloop_game --debug
 * 3. Check game.log in directory where game running.
*/
