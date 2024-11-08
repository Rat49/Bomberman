#include "LogModule/LogManager.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "PackageTool/PackageTool.hpp"

int main() 
{
	PackageTool p;
	if (!p.createPackageFile())
	{
		return 1;
	}
	p.copyPackageToFolders();
    return 0;
}