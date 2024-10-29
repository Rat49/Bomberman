#include "StringUtils.hpp"

std::vector<std::string> StringUtils::explode(const std::string& textToExplode, char delim)
{
	std::vector<std::string> result;
	std::istringstream iss(textToExplode);
	for (std::string token; std::getline(iss, token, delim); )
	{
		result.push_back(std::move(token));
	}
	return result;
}