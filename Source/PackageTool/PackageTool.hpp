#pragma once
#include <string>
#include <fstream>
#include "PackageToolTypes.hpp"
#include "ConfigSystem/ConfigFile.hpp"

class LogManager;
class ConfigSystem;

class PackageTool
{
public:
	PackageTool();

	bool createPackageFile();

	void copyPackagetoFolders();

private:
	std::unique_ptr<LogManager> Logs;
	std::unique_ptr<ConfigSystem> Config;
	ConfigFile packageConfig;
	bool addToPackage(const std::string& filePath, PkgAsset& outPkgAsset, std::ostream& outputFile);

};
