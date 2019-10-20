#pragma once
#ifndef _config_manager_fwd_
#define _config_manager_fwd_
#include <iostream>
#include <map>
using std::map;
using std::string;
using std::ifstream;
using std::stringstream;
namespace xcstd {
	class ConfigManager {
	public:
		ConfigManager() = delete;
		ConfigManager(string);
		~ConfigManager()=default;
		bool AddNewInfo(string,string);
		bool DeleteOldInfo(string);
		bool ReplaceOldInfo(string,string);
		string GetValue(string);
		bool IsFirstRun();
	private:
		bool isFirstRun = false;
		map<string, string> map_info;
		string info_path;
		bool loadFromFile();
		bool saveToFile();
		bool findKeyExist(string);
		void loadToPair(ifstream&);
	};
}
#endif

