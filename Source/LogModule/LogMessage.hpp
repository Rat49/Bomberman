#pragma once
#include "LogModule/LogMessageInterface.hpp"


class LogMessage : public LogMessageInterface
{
public:
    LogMessage(const LogLevel& level, const LogChannel& channel, const std::string& text)
        : mText(text), mLogLevel(level), mLogChannel(channel) {};

    const std::string GetText() const override
    {
        return mText;
    };
    const LogLevel GetLevel() const override
    {
        return mLogLevel;
    };
    const LogChannel GetChannel() const override
    {
        return mLogChannel;
    };

private:
    std::string mText;
    LogLevel    mLogLevel;
    LogChannel  mLogChannel;
};
