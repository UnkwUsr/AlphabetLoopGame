#include <ctime>
#include <string>


class Timer {
	public:
		Timer();

		std::string getDifferentStringify();

		void pause();
		void continu();
	private:
		time_t start;

		time_t pausedtime;
		time_t pausestart;

		const time_t GMT3 = 3 * 60 * 60;
};