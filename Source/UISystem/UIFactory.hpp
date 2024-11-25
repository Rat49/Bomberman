#pragma once
#include <string>

class UIScreen;
class ConfigSection;

namespace UIFactory
{
	void makeScreen(const std::string& path, UIScreen* screen, const std::string& screenFont);

	void makeUILabel(UIScreen* screen, const std::string& screenFont, const ConfigSection& element);
};