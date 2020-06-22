#include "config.h"
#include "config/cvars.h"

#include <fstream>
#include <sstream>

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
    std::ifstream configfile(FILENAME);

    if(configfile.is_open())
    {
        std::string line;
        while(getline(configfile, line))
            parseLine(line);
    }
}

void Config::parseLine(std::string line)
{
    if(line == "") return;

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
            // TODO: написать чтобы можно было биндить такие кнопки как F1, ENTER, и т.д.
            // в Input добавить std::map<std::string, int> special_keys
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
    if(*next_word == "")
        throw 1337;
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

void Config::saveConfig()
{
    /* std::ofstream configfile(FILENAME); */

    // TODO: in class Cvars add function getCvarsList and get it there
    /* for(auto &item : cvars->cvars_list) */
    /* { */
    /*     std::string name = item.first; */
    /*     configfile << name << " "; */

    /*     cvar cvr = item.second; */
    /*     if(cvr.type == CVAR_INT) */
    /*     { */
    /*         int* int_ptr = static_cast<int*>(cvr.ptr); */
    /*         configfile << *int_ptr; */
    /*     } */
    /*     else if(cvr.type == CVAR_STR) */
    /*     { */
    /*         std::string* string_ptr = static_cast<std::string*>(cvr.ptr); */
    /*         configfile << *string_ptr; */
    /*     } */
    /*     else if(cvr.type == CVAR_BOOL) */
    /*     { */
    /*         bool* string_ptr = static_cast<bool*>(cvr.ptr); */
    /*         configfile << *string_ptr; */
    /*     } */
    /*     configfile << std::endl; */
    /* } */

    /* configfile.close(); */
}
