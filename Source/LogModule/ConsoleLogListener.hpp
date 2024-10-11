#pragma once
#include "LogModule/BaseLogListener.hpp"
#include <iostream>


class ConsoleLogListener : public BaseLogListener
{
public:
	ConsoleLogListener(const uint16_t& levelMask, const uint16_t& channelMask)
		: BaseLogListener(levelMask, channelMask)
	{
	}

	~ConsoleLogListener()
	{
	}

private:
	void Write(const std::string& text) override
	{
		std::cout << text << "\n";
	}
};
