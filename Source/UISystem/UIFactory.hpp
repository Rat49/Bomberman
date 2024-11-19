#pragma once
#include <string>

class UIScreen;
class ConfigSection;

class UIFactory
{
public:

	static UIFactory& getInstance() {
		static UIFactory instance;
		return instance;
	}

	void makeScreen(const std::string& path, UIScreen* screen, const std::string& screenFont);

	void makeUILabel(UIScreen* screen, const std::string& screenFont, const ConfigSection& element);
};