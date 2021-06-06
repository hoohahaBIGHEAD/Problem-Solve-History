#pragma once

enum class Mode
{
	WriteOnFile = 1,
	PrintOnScreen = 2,
	All = 3
};

inline Mode operator|(Mode a, Mode b)
{
	return static_cast<Mode>(static_cast<int>(a) | static_cast<int>(b));
}
inline Mode operator&(Mode a, Mode b)
{
	return static_cast<Mode>(static_cast<int>(a) & static_cast<int>(b));
}