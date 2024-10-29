#include "StringUtils.hpp"

size_t StringUtils::tokenize(const std::string& source, char delim, std::vector<std::string>& tokens)
{
	std::istringstream iss(source);
	std::string token;
	while (std::getline(iss, token, delim))
	{
		tokens.push_back(std::move(token));
	}
	return tokens.size();
}