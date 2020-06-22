#include "functions/timer.h"


Timer::Timer()
{
}

void Timer::reset()
{
    start = time(NULL);
    pausedtime = 0;

    ispaused = false;
}

std::string Timer::getDifferentStringify()
{
	char buffer[80];
	time_t timediff = ((time(NULL) - pausedtime)- start) - GMT3;
	strftime(buffer, 80, "%H:%M:%S", localtime(&timediff));
	return std::string(buffer);
}


void Timer::pause()
{
	pausestart = time(NULL);

    ispaused = true;
}

bool Timer::isPaused()
{
    return ispaused;
}

void Timer::continu()
{
	time_t lossedtime = time(NULL) - pausestart;

	pausedtime += lossedtime;

    ispaused = false;
}
