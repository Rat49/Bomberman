#include "Common/Modules.hpp"
#include "LogModule/LogManager.hpp"

// logs could be used only while development
#ifndef FINAL
	#define LOG(...) Modules::Logs->Log(__VA_ARGS__)
#else
	#define LOG(...) 
#endif