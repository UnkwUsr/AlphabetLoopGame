#ifndef CONTROL_H
#define CONTROL_H

#include "map.h"
#include <string>
#include <map>
#include <vector>


struct scroll_arg {
    int dir;
    unsigned int num;
};
class Control {
    public:
        Control(Map *_map);
        ~Control();

        bool resolveAction(std::string act);

        unsigned int amountscrolls;

        void randomizeMap();
        std::vector<scroll_arg> scrolls_history;

    private:
        Map *map;

        void initScrollFuncs();

        enum {DIR_LEFT = 1, DIR_RIGHT = -1, DIR_UP = 2, DIR_DOWN = -2};
        std::map<std::string, scroll_arg> actions_scrolls;
        void doScroll(int dir, unsigned int num);

        void undoScroll();
};

#endif
