#include "config.h"

#include <fstream>
#include <sstream>

#include "logging.h"


Config::Config()
{
    cvars = new Cvars();

    readConfig();
}

Config::~Config()
{
    delete cvars;
}

void Config::readConfig()
{
    std::ifstream configfile(CONFIG_FILENAME);

    if(configfile.good())
    {
        if(configfile.is_open())
        {
            std::string line;
            while(getline(configfile, line))
                parseLine(line);
        }
        else
            logfile << "Can't open config file" << std::endl;
    }
    else
    {
        bindKey('q', "exit");
        bindKey('r', "restart");

        bindKey('o', "see_completed_map");
        bindKey('i', "set_highlighting");

        bindKey('w', "undo_scroll");
        // by default map has size 5x5, so we generate bindings for it
        std::string horizontal_swipes = "asdfg";
        std::string vertical_swipes = "zxcvb";
        int i = 0;
        for(char m : horizontal_swipes)
        {
            bindKey(m, "scroll_left_" + std::to_string(i));
            bindKey(toupper(m), "scroll_right_" + std::to_string(i));
            i++;
        }
        i = 0;
        for(char m : vertical_swipes)
        {
            bindKey(m, "scroll_up_" + std::to_string(i));
            bindKey(toupper(m), "scroll_down_" + std::to_string(i));
            i++;
        }

        writeConfig();
    }
}

void Config::parseLine(std::string line)
{
    if(line == "")
        return;

    try
    {
        std::istringstream lnstream(line);

        std::string keyword;
        getNextWord(&lnstream, &keyword);
        int keyword_type = parseKeyWord(&keyword);
        if(keyword_type == KEYWORD_CVAR)
        {
            std::string name;
            getNextWord(&lnstream, &name);
            std::string value;
            getNextWord(&lnstream, &value);

            if(value[0] == '"')
            {

                int trimlastchar = 1; // 1 is because need trim first "
                if(value[value.length() - 1] == '"')
                    trimlastchar = 2; // 2 is because need trim last "
                value = line.substr((keyword.length() + name.length()) + 1, value.length() - trimlastchar);
            }
            cvars->setCvarValue(name, value);
        }
        else if(keyword_type == KEYWORD_BIND)
        {
            std::string key;
            getNextWord(&lnstream, &key);
            std::string action;
            getNextWord(&lnstream, &action);

            bindKey(key[0], action);
        }
    } catch(int i) {
        return;
    }
}

void Config::getNextWord(std::istringstream *lnstream, std::string *next_word)
{
    getline(*lnstream, *next_word, ' ');
}

int Config::parseKeyWord(std::string *word)
{
    if(word->compare("cvar") == 0)
        return KEYWORD_CVAR;
    else if(word->compare("bind") == 0)
        return KEYWORD_BIND;

    else
        return KEYWORD_UNKNOWN;
}

void Config::bindKey(char key, std::string command)
{
    binds[key] = command;
}


std::string Config::getActionByKey(char key)
{
    auto it = binds.find(key);
    if(it != binds.end())
        return it->second;
    else
        return ACTION_NULL;
}

void Config::writeConfig()
{
    std::ofstream configfile(CONFIG_FILENAME);

    configfile << "// Cvars:" << std::endl;
    cvars->writeCvars(configfile);
    configfile << std::endl;

    configfile << "// Binds:" << std::endl;
    for(auto &item : binds)
    {
        const char key = item.first;
        std::string act = item.second;

        configfile << "bind " << key << " " << act << std::endl;
    }

    configfile.close();
}
