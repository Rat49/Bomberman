#pragma once
#include "LogModule/LogListenerInterface.hpp"


class BaseLogListener : public LogListenerInterface
{
public:
    BaseLogListener(const uint16_t& levelMask, const uint16_t& channelMask)
        : mLevelMask(levelMask), mChannelMask(channelMask)
    {
    }

    const uint16_t GetLevelMask() const
    {
        return mLevelMask;
    }
    const uint16_t GetChannelMask() const
    {
        return mChannelMask;
    }

    void Handle(const LogMessageInterface& message) override;
    void Handle(const LogLevel& level, const LogChannel& channel, const std::string& text) override;

private:
    uint16_t mLevelMask;
    uint16_t mChannelMask;

    virtual void Write(const std::string& text) = 0;
};
