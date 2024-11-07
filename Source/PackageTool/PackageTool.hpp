#pragma once
#include <string>
#include <fstream>
#include "PackageToolTypes.hpp"

class LogManager;
class ConfigSystem;

class PackageTool
{
public:
	PackageTool();

	bool createPackageFile();

private:
	std::unique_ptr<LogManager> Logs;
	std::unique_ptr<ConfigSystem> Config;
	bool addToPackage(const std::string& filePath, PkgAsset& outPkgAsset, std::ostream& outputFile);

};
