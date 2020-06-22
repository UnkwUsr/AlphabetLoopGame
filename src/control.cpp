#include "control.h"
#include "common.h"


Control::Control(Map *_map)
{
    map = _map;

    initScrollFuncs();
}

Control::~Control()
{}

void Control::initScrollFuncs()
{
    const std::string SCROLL = "scroll_";

    actions_scrolls.clear();
    for(unsigned int i = 0; i < HORIZ_LEN; ++i)
    {
        actions_scrolls[SCROLL + "up_" + std::to_string(i)] = {DIR_UP, i};
        actions_scrolls[SCROLL + "down_" + std::to_string(i)] = {DIR_DOWN, i};
    }
    for(unsigned int i = 0; i < VERT_LEN; ++i)
    {
        actions_scrolls[SCROLL + "left_" + std::to_string(i)] = {DIR_LEFT, i};
        actions_scrolls[SCROLL + "right_" + std::to_string(i)] = {DIR_RIGHT, i};
    }
}

void Control::doScroll(int dir, unsigned int num)
{
    if(dir == DIR_LEFT)
        map->scrollLeft(num);
    else if(dir == DIR_RIGHT)
        map->scrollRight(num);
    else if(dir == DIR_UP)
        map->scrollUp(num);
    else if(dir == DIR_DOWN)
        map->scrollDown(num);
}

bool Control::resolveAction(std::string act)
{
    auto it = actions_scrolls.find(act);
    if(it != actions_scrolls.end())
    {
        scroll_arg scroll = it->second;

        bool temp = false;
        if(AUTO_UNDO_SAME_SCROLLS && !scrolls_history.empty())
        {
            scroll_arg lastscroll = scrolls_history.back();
            if(scroll.num == lastscroll.num && scroll.dir == lastscroll.dir * -1)
            {
                undoScroll();
                temp = true;
            }
        }
        if(!temp)
        {
            scrolls_history.push_back(scroll);
            doScroll(scroll.dir, scroll.num);
            amountscrolls++;
        }

        return true;
    }
    else if(act == "undo_scroll")
    {
        undoScroll();
        return true;
    }
    else
        return false;
}

void Control::undoScroll()
{
    if(!scrolls_history.empty())
    {
        scroll_arg lastscroll = scrolls_history.back();
        scrolls_history.pop_back();

        lastscroll.dir *= -1;
        doScroll(lastscroll.dir, lastscroll.num);

        amountscrolls--;
    }
}

void Control::randomizeMap()
{
    if(RANDOMIZE_MAP)
    {
        unsigned int rnd_steps = MIN_RAND_STEPS + rand() % MAX_RAND_STEPS;
        for(unsigned int i = 0; i < rnd_steps; ++i)
        {
            unsigned int rnd_num = 0;
            int rnd_dir = DIR_LEFT + rand() % DIR_DOWN;

            if(rnd_dir == DIR_LEFT || rnd_dir == DIR_RIGHT)
                rnd_num = 0 + rand() % VERT_LEN;
            else if(rnd_dir == DIR_UP || rnd_dir == DIR_DOWN)
                rnd_num = 0 + rand() % HORIZ_LEN;

            doScroll(rnd_dir, rnd_num);
        }
    }
}
