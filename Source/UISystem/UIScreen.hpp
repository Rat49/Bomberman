#pragma once

#include "UISystem/UIElement.hpp"
#include "UISystem/UISystem.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Font.hpp>
#include "SpriteModule/Animation.hpp"
#include <vector>
#include <memory>

class UIScreen : public UIElement
{
public:
	// Add a UI element
	void addElement(const std::string& elementName, const std::shared_ptr<UIElement> element);

	// Get a UI element
	std::shared_ptr<UIElement> getElement(const std::string& elementName) const;

	// Remove a UI element
	void removeElement(const std::string& element);

	// Add animation
	void addAnimation(const std::string& animationName, const std::shared_ptr<Animation> animation);

	// Get animation
	std::shared_ptr<Animation> getAnimation(const std::string& animationName) const;

	// Remove animation
	void removeAnimation(const std::string& animationName);

	// Set the view for the UI screen
	void setView(const sf::View& view);

	// Clear all UI elements from the screen
	void clearElements();

	bool handleEvent(const sf::Event& event) override;

	// Set the render window for event handling
	void setWindow(sf::RenderWindow* renderWindow) { window = renderWindow; }

	// Get the render window
	sf::RenderWindow* getWindow() const { return window; }

	// A method that returns a reference to the requested font
	static sf::Font& getFont(const std::string& fontName);

	void updateUIElementPositions();

	// Override draw method to draw all UI elements on the given target
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const sf::Color& getBackgroundColor() { return backgroundColor; }

	void setBackgroundColor(const sf::Color& newColor) { backgroundColor = newColor; }

protected:
	// Map to store UI elements
	std::unordered_map<std::string, std::shared_ptr<UIElement>> elements;

	// Map to store animations
	std::unordered_map<std::string, std::shared_ptr<Animation>> animations;

	// Optional view for handling UI viewport settings
	sf::View view;

	// Pointer to the render window
	sf::RenderWindow* window = nullptr;

	// Flag to check if view is set
	bool viewSet = false;

	// Map that caches loaded fonts
	static std::unordered_map<std::string, sf::Font> fonts;

	UISystem* uiSystem;

	sf::Color backgroundColor;
};
