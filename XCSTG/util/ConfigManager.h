#pragma once
#ifndef _config_manager_fwd_
#define _config_manager_fwd_
#include <iostream>
#include <map>
using std::map;
using std::string;
using std::ifstream;
using std::stringstream;
namespace xc_std {
	class ConfigManager {
	public:
		ConfigManager() = delete;
		explicit ConfigManager(string);
		~ConfigManager()=default;
		bool AddNewInfo(string,string);
		bool DeleteOldInfo(string);
		bool ReplaceOldInfo(string,string);
		stringstream GetValue(string);
		bool IsFirstRun();
	private:
		bool isFirstRun = false;
		map<string, string> map_info;
		string info_path;
		bool load_from_file();
		bool save_to_file();
		bool find_key_exist(string);
		void load_to_pair(ifstream&);
	};
}
#endif

