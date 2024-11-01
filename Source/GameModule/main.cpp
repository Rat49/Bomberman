#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include <fstream>
#include <Windows.h>


int WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nShowCmd*/)
{
#ifndef FINAL
    if (AllocConsole())
    {
        FILE* StreamOut = nullptr;
        FILE* StreamIn = nullptr;
        freopen_s(&StreamOut, "CONOUT$", "wt", stdout);
        freopen_s(&StreamIn, "CONIN$", "rt", stdin);
        SetConsoleTitle("Debug Console");
        std::ios::sync_with_stdio(1);
    }
#endif

	if (!Modules::initialize()) {
		return -1;
	}
    Modules::Game->run();

    Modules::terminate();

    return 0;
}