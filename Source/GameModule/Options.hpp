#pragma once
#include "UISystem/UIScreen.hpp"
#include <unordered_set>

class UIInputField;

class Options : public UIScreen
{
public:
	Options(sf::RenderWindow* renderWindow, const std::string& optionsFont, const std::string& pathToIniFile);

	bool handleEvent(const sf::Event& event) override;
	
private:
	std::unordered_map<std::string, std::vector<std::string>> screens;

	std::unordered_set<std::string> registeredKeys;

	// Read all sections and its elements, that are stored in config file
	void readScreens();

	// Hide current screen if exists, and show new screen
	void showScreen(const std::string& name);

	void remapKey(std::shared_ptr<UIInputField> inputField, const sf::Event& event, const std::string& elementName);

	bool checkDuplicates(const std::string& newKey, const std::string& oldKey);

	// Set new value for selected resolution
	void setResolutionLabel(float value);

	void hideScreen();

	std::string currentScreen;

	std::pair<uint32_t, uint32_t> currentWindowSize;

	std::pair<uint32_t, uint32_t> changedWindowSize;

	bool fullscreen = false;
};