#pragma once
#include <string>

class UIScreen;
class ConfigSection;

namespace UIFactory
{
	void makeScreen(const std::string& path, UIScreen* screen, const std::string& screenFont);

	void setUIScreen(UIScreen* screen, const ConfigSection& element);

	void makeUILabel(UIScreen* screen, const std::string& screenFont, const ConfigSection& element);

	void makeAnimation(UIScreen* screen, const ConfigSection& element);

	void makeUIButton(UIScreen* screen, const std::string& screenFont, const ConfigSection& element);
};