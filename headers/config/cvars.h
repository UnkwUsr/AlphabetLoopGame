#ifndef CVARS_H
#define CVARS_H

#include <string>
#include <map>



class Cvars {
	public:
		Cvars();

		struct cvar
		{
			int type;
			void* ptr;
		};
		enum {TYPE_INT, TYPE_STR, TYPE_BOOL};

		void setCvarValue(std::string name, std::string value);

		void* getCvar(const char* name);
	private:
		std::map<std::string, cvar> cvars_list;

		void initCvar(std::string name, void* ptr, int type);
};

#endif