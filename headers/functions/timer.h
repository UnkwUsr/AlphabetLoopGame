#include <ctime>
#include <string>


class Timer {
	public:
		Timer();

		std::string getDifferentStringify();

		void pause();
		void continu();
        void reset();

        bool isPaused();
	private:
		time_t start;

		time_t pausedtime;
		time_t pausestart;

        bool ispaused;

		const time_t GMT3 = 3 * 60 * 60;
};
