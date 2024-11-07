#include <iostream>
#include "LogModule/LogManager.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "PackageTool/PackageTool.hpp"

int main() 
{
	PackageTool p;
	p.createPackageFile();
	std::cin.get();
	return 1;
}