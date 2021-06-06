#pragma once

#include "Logger.h"
#include <string>
#include <Windows.h>
#include <iostream>
#include "FileManage.h"

using namespace std;

/// <summary>
/// 클래스 생성 factory
/// </summary>
/// <param name="file_name">사용되는 파일 위치. __FILE__을 사용한다</param>
/// <param name="mode">출력 모드 설정</param>
/// <param name="log_type">사용될 로그 타입들</param>
/// <returns>생성된 클래스를 반환</returns>
Logger Logger::log_create(string file_name, string function_name, Mode mode, LogType log_type)
{
	Logger logger = Logger();
	logger.file_name = file_name;
	logger.function_name = function_name;
	logger.log_type = log_type;
	logger.mode = mode;

	/*if (file_manager == NULL) {
		file_manager = new FileManager();
	}*/

	return logger;
}
/// <summary>
/// 로그 출력
/// </summary>
/// <param name="type">로그 타입</param>
/// <param name="log_data">출력할 내용</param>
/// <param name="line">호출되는 위치. __LINE__를 사용한다</param>
void Logger::log_print(LogType type, std::string log_data, int line)
{
	// 지원하지 않는 로그 타입인 경우 메소드 종료
	if ((int)(this->log_type & type) == 0) return;
	
	// 출력할 로그가 현재의 로그 모드에 포함될 때에만 출력
	if (this->log_type < type) return;

	string message = Logger::get_log_type_char(type) + ": " + get_current_time() + ":" + this->file_name + ":" + this->function_name + "(" + to_string(line) + ")";
	
	char cmessage[1024];
	char clog_data[1024];
	strcpy_s(cmessage, message.length() + 1, message.c_str());
	strcpy_s(clog_data, log_data.length() + 1, log_data.c_str());

	switch (this->mode)
	{
	// 파일 출력하기
	case Mode::WriteOnFile: {
		LOGlogging(__FILE__, cmessage, clog_data);
		break;
	}
	// print 옵션이 활성화된 경우 화면에 출력
	case Mode::PrintOnScreen: {
		printf("%-130.1024s : %10.1024s\n", cmessage, clog_data);
		break;
	}
	case Mode::All: {
		LOGlogging(__FILE__, cmessage, clog_data);
		printf("%-130.1024s : %10.1024s\n", cmessage, clog_data);
		break;
	}
	default:
		break;
	}
	
}

/// <summary>
/// 가지고 있는 모든 flag 속성에 따라 어떤 타입의 로그인지 출력한다
/// </summary>
/// <param name="type">로그 타입</param>
/// <returns>로그 타입에 따라 변환된 문자열</returns>
string Logger::get_log_type_char(LogType type)
{
	string result = "";
	if ((int)(type & LogType::Error  ) != 0) result += "[ Error ]";
	if ((int)(type & LogType::Warning) != 0) result += "[Warning]";
	if ((int)(type & LogType::Event  ) != 0) result += "[ Event ]";
	if ((int)(type & LogType::Debug  ) != 0) result += "[ Debug ]";
	return result;
}

/// <summary>
/// 현재 시간을 로거 클래스에서 사용되는 형식으로 출력한다. yyyymmddhhmmssss
/// </summary>
/// <returns>형식에 맞게 변환된 현재 시간 문자열</returns>
std::string Logger::get_current_time()
{
	SYSTEMTIME cur_time;
	GetLocalTime(&cur_time);
	return attach_leading_zero(to_string(cur_time.wYear), 4)
		+ attach_leading_zero(to_string(cur_time.wMonth), 2)
		+ attach_leading_zero(to_string(cur_time.wDay), 2)
		+ attach_leading_zero(to_string(cur_time.wHour), 2)
		+ attach_leading_zero(to_string(cur_time.wMinute), 2)
		+ attach_leading_zero(to_string(cur_time.wSecond), 2)
		+ attach_leading_zero(to_string(cur_time.wMilliseconds), 3);
}

/// <summary>
/// get_current_time()에서 앞에 0을 붙이는 데 사용된다.
/// </summary>
/// <param name="origin">원본 문자열</param>
/// <param name="total_length">전체 문자열 길이</param>
/// <returns>0이 붙어진 문자열</returns>
string Logger::attach_leading_zero(string origin, int total_length)
{
	return string(total_length - origin.length(), '0') + origin;
}