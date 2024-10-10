#pragma once
#include "LogModule/LogListenerInterface.hpp"
#include "LogModule/StringHelper.hpp"
#include <list>

class LogManager
{

public:
	void Init();

	void AddListener(LogListenerInterface* listener) { mLlistenersList.push_back(listener); };

	void Log(const LogMessageInterface& message) const
	{
		for (LogListenerInterface* listener : mLlistenersList)
		{
			listener->Handle(message);
		}
	}

	void Log(const LogLevel& level, const LogChannel& channel, const std::string& str) const
	{
		for (LogListenerInterface* listener : mLlistenersList)
		{
			listener->Handle(level, channel, str);
		}
	}

	template<typename... Targs>
	void Log(const LogLevel& level, const LogChannel& channel, const std::string& fstr, const Targs& ... args) const
	{
		Log(level, channel, StringHelper::Format(fstr, args...));
	}

	template<typename... Targs>
	void Log(const std::string& fstr, const Targs& ... args) const
	{
		Log(LogLevel::DEBUG, LogChannel::MAIN, fstr, args...);
	};

private:
	std::list<LogListenerInterface*> mLlistenersList;

};
