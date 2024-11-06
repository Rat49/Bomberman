#pragma once
#include <string>
#include <fstream>
#include <map>
#include "PackageToolTypes.hpp"

class LogManager;

class PackageTool
{
public:
	PackageTool();

	bool createPackageFile();

private:
	std::unique_ptr<LogManager> Logs;
	bool addToPackage(const std::string& filePath, PkgAsset& outPkgAsset, std::ostream& outputFile);

};
