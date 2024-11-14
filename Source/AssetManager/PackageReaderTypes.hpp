#pragma once
#include <fstream>

struct AssetMetadata
{
	std::string assetName;
	std::streamoff offset;
	std::streamoff size;
};