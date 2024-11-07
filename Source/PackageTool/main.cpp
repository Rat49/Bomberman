#include <iostream>
#include "LogModule/LogManager.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "PackageTool/PackageTool.hpp"

int main() 
{
	PackageTool p;
	if (p.createPackageFile())
	{
		p.copyPackageToFolders();
	}
	std::cin.get();
	return 1;
}