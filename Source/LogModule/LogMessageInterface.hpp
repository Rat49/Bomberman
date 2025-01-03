#pragma once
#include <string>

enum struct LogLevel : uint16_t
{
    DEBUG = 1,
    INFO  = 2,
    WARN  = 4,
    FATAL = 8
};

enum struct LogChannel : uint16_t
{
    MAIN = 1
};

class LogMessageInterface
{
public:
    virtual const LogLevel    GetLevel() const   = 0;
    virtual const LogChannel  GetChannel() const = 0;
    virtual const std::string GetText() const    = 0;
};
