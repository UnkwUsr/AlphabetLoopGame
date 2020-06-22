#include "config/cvars.h"


// map
int HORIZ_LEN = 5;
int VERT_LEN = 5;

// screen
int BLOCK_SIZE = 2;

int HORIZ_INDENT = BLOCK_SIZE;
int VERT_INDENT = HORIZ_INDENT / 2;

int HORIZ_SPACES_NUM = BLOCK_SIZE;
int VERT_SPACES_NUM = HORIZ_SPACES_NUM / 2;

// functions
std::string RECORDS_FILENAME = "records.txt";
bool AUTO_UNDO_SAME_SCROLLS = true;
// debug
bool RANDOMIZE_MAP = true;
int MIN_RAND_STEPS = 100;
int MAX_RAND_STEPS = 500;

Cvars::Cvars()
{
    // map
    initCvar("horiz_len", &HORIZ_LEN, TYPE_INT);
    initCvar("vert_len", &VERT_LEN, TYPE_INT);

    // screen
    initCvar("block_size", &BLOCK_SIZE, TYPE_INT);

    initCvar("horiz_indent", &HORIZ_INDENT, TYPE_INT);
    initCvar("vert_indent", &VERT_INDENT, TYPE_INT);

    initCvar("horiz_spaces_num", &HORIZ_SPACES_NUM, TYPE_INT);
    initCvar("vert_spaces_num", &VERT_SPACES_NUM, TYPE_INT);

    // functions
    initCvar("records_filename", &RECORDS_FILENAME, TYPE_STR);
    initCvar("auto_undo_same_scrolls", &AUTO_UNDO_SAME_SCROLLS, TYPE_BOOL);
    // debug
    initCvar("min_rand_steps", &MIN_RAND_STEPS, TYPE_INT);
    initCvar("max_rand_steps", &MAX_RAND_STEPS, TYPE_INT);
    initCvar("randomize_map", &RANDOMIZE_MAP, TYPE_BOOL);
}

void Cvars::initCvar(std::string name, void* ptr, int type)
{
    cvars_list[name] = {type, ptr};
}


void Cvars::setCvarValue(std::string name, std::string value)
{
    auto it = cvars_list.find(name);
    if(it != cvars_list.end())
    {
        cvar thiscvar = it->second;

        if(thiscvar.type == TYPE_INT)
        {
            int* int_ptr = static_cast<int*>(thiscvar.ptr);
            try {
                *int_ptr = std::stoi(value);
            } catch(...) {
                *int_ptr = 0;
            }
        }
        else if(thiscvar.type == TYPE_STR)
        {
            std::string* string_ptr = static_cast<std::string*>(thiscvar.ptr);
            *string_ptr = value;
        }
        else if(thiscvar.type == TYPE_BOOL)
        {
            bool* bool_ptr = static_cast<bool*>(thiscvar.ptr);
            if(value.compare("1") == 0)
                *bool_ptr = true;
            else
                *bool_ptr = false;
        }
    }
}

void Cvars::writeCvars(std::ofstream &configfile)
{
    for(auto &item : cvars_list)
    {
        std::string name = item.first;
        configfile << "cvar " << name << " ";

        Cvars::cvar cvr = item.second;
        if(cvr.type == TYPE_INT)
        {
            int* int_ptr = static_cast<int*>(cvr.ptr);
            configfile << *int_ptr;
        }
        else if(cvr.type == TYPE_STR)
        {
            std::string* string_ptr = static_cast<std::string*>(cvr.ptr);
            configfile << *string_ptr;
        }
        else if(cvr.type == TYPE_BOOL)
        {
            bool* string_ptr = static_cast<bool*>(cvr.ptr);
            configfile << *string_ptr;
        }
        configfile << std::endl;
    }
}

// DEBUG func:
void* Cvars::getCvar(const char* name)
{
    auto it = cvars_list.find((std::string)name);
    if(it != cvars_list.end())
        return it->second.ptr;
    else
        return NULL;
}

