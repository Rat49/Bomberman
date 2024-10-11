#include "LogModule/BaseLogListener.hpp"


void BaseLogListener::Handle(const LogMessageInterface& message)
{
	Handle(message.GetLevel(), message.GetChannel(), message.GetText());
}

void BaseLogListener::Handle(const LogLevel& level, const LogChannel& channel, const std::string& text)
{
	if (GetLevelMask() & static_cast<uint16_t>(level) && GetChannelMask() & static_cast<uint16_t>(channel))
	{
		Write(text);
	}
}
