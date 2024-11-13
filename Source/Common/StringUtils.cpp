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

void StringUtils::cipherText(std::string& textToCipher, const std::string& key)
{
	for (int i = 0; i < textToCipher.size(); ++i)
	{
		textToCipher[i] = textToCipher[i] ^ key[i % (key.size())];
	}
}