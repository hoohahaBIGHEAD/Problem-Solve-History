#pragma once

#include<string>
#include"LogType.h"
#include"Mode.h"

using namespace std;
class Logger
{
public:
	static Logger log_create(string file_name, string function_name, Mode mode, LogType log_type);
	void log_print(LogType type, std::string log_data, int line);

private:
	string file_name;
	string function_name;
	Mode mode;
	LogType log_type;
	static string get_log_type_char(LogType type);
	static string get_current_time();
	static string attach_leading_zero(string origin, int total_length);

};
