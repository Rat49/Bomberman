#pragma once
#include "LogModule/LogManager.hpp"
#include "LogModule/FileLogListener.hpp"
#include "LogModule/ConsoleLogListener.hpp"
#include <cassert>


void LogManager::Init()
{
    constexpr auto LogFile = "Bomberman.log";
    AddListener(new FileLogListener(LogFile, UINT16_MAX, UINT16_MAX));
    AddListener(new ConsoleLogListener(UINT16_MAX, UINT16_MAX));
}
