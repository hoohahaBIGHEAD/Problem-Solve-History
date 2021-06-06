#pragma once

//- 로그 범위 옵션(error, waring, event, debug 등)
enum class LogType
{
	Error = 1,
	Warning = 2,
	Event = 4,
	Debug = 8
};

inline LogType operator|(LogType a, LogType b)
{
	return static_cast<LogType>(static_cast<int>(a) | static_cast<int>(b));
}
inline LogType operator&(LogType a, LogType b)
{
	return static_cast<LogType>(static_cast<int>(a) & static_cast<int>(b));
}