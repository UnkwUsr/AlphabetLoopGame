#ifndef MAP_H
#define MAP_H
#include <string>


class Map {
	public:
		Map();
		void reset();
		void Init();

		bool isCompleted();


		std::string getRow(int n);
		std::string getColumn(int n);

		void insertRow(int n, std::string &str);
		void insertColumn(int n, std::string &str);


		void scrollLeft(int n);
		void scrollRight(int n);

		void scrollUp(int n);
		void scrollDown(int n);

		std::string mapstr;
		std::string solvedmapstr;
	private:
		unsigned int maplen;

		const std::string TEMPLATE_MAP_STR = "abcdefghijklmnopqrstuvwxy";
};
#endif
