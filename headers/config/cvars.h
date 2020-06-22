#ifndef CVARS_H
#define CVARS_H

#include <string>
#include <map>
#include <fstream>



class Cvars {
	public:
		Cvars();

		void setCvarValue(std::string name, std::string value);

		void* getCvar(const char* name);

        void writeCvars(std::ofstream &configfile);

	private:
		struct cvar
		{
			int type;
			void* ptr;
		};
		enum {TYPE_INT, TYPE_STR, TYPE_BOOL};

		std::map<std::string, cvar> cvars_list;

		void initCvar(std::string name, void* ptr, int type);
};

#endif
