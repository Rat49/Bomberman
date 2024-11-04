#pragma once
#include <string>
#include <fstream>
#include <map>
#include "PackageManagerTypes.hpp"

class PackageManager
{
public:
	static bool createPackageFile(const std::string folderPath);

private:
	static bool loadToPackage(const std::string& filePath, PkgAsset& pkgAsset, std::ostream& outputFile);

};

