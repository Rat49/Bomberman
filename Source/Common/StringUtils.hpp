#pragma once
#include <string>
#include <vector>
#include <sstream>

class StringUtils
{
public:
	static size_t tokenize(const std::string& source, char delim, std::vector<std::string>& tokens);

	static void cipherText(std::string& textToCipher, const std::string& key);
};

