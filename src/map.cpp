#include "map.h"
#include "common.h"

#include <string>


Map::Map()
{}

void Map::Init()
{
	maplen = HORIZ_LEN * VERT_LEN;
	if(maplen <= TEMPLATE_MAP_STR.length())
		solvedmapstr = TEMPLATE_MAP_STR.substr(0, maplen);
	else
		throw("Too long HORIZ_LEN/VERT_LEN value");
}

void Map::reset()
{
	mapstr = solvedmapstr;
}


std::string Map::getRow(int n)
{
	std::string	res = mapstr.substr(n * HORIZ_LEN, HORIZ_LEN);

	return res;
}

std::string Map::getColumn(int n)
{
	std::string res;

	for(int i = n; i < maplen; i += HORIZ_LEN)
		res += mapstr[i];

	return res;
}


void Map::insertRow(int n, std::string &str)
{
	mapstr.replace(n * HORIZ_LEN, HORIZ_LEN, str);
}

void Map::insertColumn(int n, std::string &str)
{
	for(int i = n, j = 0; i < maplen; i += HORIZ_LEN, ++j)
		mapstr[i] = str[j];
}


void Map::scrollLeft(int n)
{
	std::string row = getRow(n);
	std::string res = row.substr(1, HORIZ_LEN - 1) + row.front();

	insertRow(n, res);
}

void Map::scrollRight(int n)
{
	std::string row = getRow(n);
	std::string res = row.back() + row.substr(0, HORIZ_LEN - 1);

	insertRow(n, res);
}


void Map::scrollUp(int n)
{
	std::string column = getColumn(n);
	std::string res = column.substr(1, VERT_LEN - 1) + column.front();

	insertColumn(n, res);
}

void Map::scrollDown(int n)
{
	std::string column = getColumn(n);
	std::string res = column.back() + column.substr(0, VERT_LEN - 1);

	insertColumn(n, res);
}



bool Map::isCompleted()
{
	return mapstr == solvedmapstr;
}
