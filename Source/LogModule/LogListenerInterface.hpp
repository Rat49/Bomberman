#pragma once
#include "LogModule/LogMessageInterface.hpp"


class LogListenerInterface
{
public:
	virtual void Handle(const LogMessageInterface& message) = 0;
	virtual void Handle(const LogLevel& level, const LogChannel& channel, const std::string& text) = 0;
};
