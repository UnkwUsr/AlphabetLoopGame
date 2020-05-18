#ifndef CONFIG_H
#define CONFIG_H

#include "config/cvars.h"

#include <string>
#include <map>



class Config {
    public:
        Config();
        ~Config();

        const char* FILENAME = "config.cfg";

        std::string getActionByKey(char key);
        std::string ACTION_NULL = "";

        std::map<char, std::string> binds;
        void bindKey(char key, std::string command);
        void readConfig();
    private:
        Cvars* cvars;

        void parseLine(std::string line);

        enum {KEYWORD_UNKNOWN, KEYWORD_CVAR, KEYWORD_BIND};
        int parseKeyWord(std::string *word);

        void getNextWord(std::istringstream *linestream, std::string *next_word);

        // void setCvar?
};

#endif
