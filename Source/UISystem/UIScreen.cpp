#include "UISystem/UIScreen.hpp"
#include "UISystem/UISystem.hpp"
#include "UISystem/UIButton.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Common/Logs.hpp"

namespace {
	const std::string BASE_PATH = "Game/Fonts/";
	const std::string FILE_EXTENSION = ".ttf";
}

// Add a UI element
void UIScreen::addElement(const std::string& elementName, const std::shared_ptr<UIElement> element)
{
	// Check for null pointer
	if (element) {
		if (elements.find(elementName) == elements.end()) {
			elements[elementName] = element;
		}
		else {
			LOG("Error: adding element to UIScreen with name that already exists");
		}
	}
	else {
		LOG("Error: adding nullptr element to UIScreen");
	}
}

std::shared_ptr<UIElement> UIScreen::getElement(const std::string& elementName) const
{
	auto it = elements.find(elementName);
	if (it != elements.end()) {
		return it->second;
	}
	return nullptr;
}

// Remove a UI element
void UIScreen::removeElement(const std::string& element)
{
	// Find the element
	auto it = elements.find(element);
	if (it != elements.end())
	{
		elements.erase(it);
	}
}

void UIScreen::addAnimation(const std::string& animationName, const std::shared_ptr<Animation> animation)
{
	// Check for null pointer
	if (animation) {
		if (animations.find(animationName) == animations.end()) {
			animations[animationName] = animation;
		}
		else {
			LOG("Error: adding animation to UIScreen with name that already exists");
		}
	}
	else {
		LOG("Error: adding nullptr animation to UIScreen");
	}
}

std::shared_ptr<Animation> UIScreen::getAnimation(const std::string& animationName) const
{
	auto it = animations.find(animationName);
	if (it != animations.end()) {
		return it->second;
	}
	return nullptr;
}

void UIScreen::removeAnimation(const std::string& animationName)
{
	// Find the element
	auto it = animations.find(animationName);
	if (it != animations.end())
	{
		it->second->Stop();
		animations.erase(it);
	}
}

// Draw all UI elements on the given target
void UIScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Check if a custom view is set and apply it
	if (viewSet)
	{
		// Set the custom view if available
		target.setView(view);
	}

	sf::RectangleShape tempBackground = background;

	// Draw the background
	target.draw(tempBackground, states);

	// Draw each UI element on the given target
	for (const auto& element : elements)
	{
		// Check if the element is visible before drawing
		if (element.second->isVisible())
		{
			target.draw(*element.second, states);
		}
	}
	for (const auto& animation : animations)
	{
		// Check if the element is visible before drawing
		if (animation.second->isPlaying())
		{
			target.draw(*animation.second, states);
		}
	}

	// Restore the default view if a custom view was set
	if (viewSet)
	{
		target.setView(target.getDefaultView());
	}
}

const sf::Font& UIScreen::getFont(const std::string& fontName)
{
	const std::string assetPath = BASE_PATH + fontName + FILE_EXTENSION;

	std::shared_ptr<sf::Font> fontPtr = std::make_shared<sf::Font>();
	fontPtr = Modules::Assets->getFont(assetPath);

	return *fontPtr;
}

// Set the view for the UI screen
void UIScreen::setView(const sf::View& newView)
{
	view = newView;

	// Mark that a custom view has been set
	viewSet = true;
}

// Clear all UI elements from the screen
void UIScreen::clearElements()
{
	elements.clear();
}

bool UIScreen::handleEvent(const sf::Event& event)
{
	// If no window is set, exit the method
	if (!window)
	{
		return false;
	}

	if (event.type == sf::Event::Resized)
	{
		updateUIElementPositions();
	}

	return true;
}

void UIScreen::updateUIElementPositions()
{
	const auto scale = Modules::UI->getScale();
	for (auto& element : elements)
	{
		element.second->handleResize(scale);
	}
	for (auto& animation : animations)
	{
		animation.second->handleResize(scale);
	}
	setBackground(background.getPosition().x * scale.x, background.getPosition().y * scale.y,
		background.getSize().x * scale.x, background.getSize().y * scale.y, background.getFillColor() );
}

void UIScreen::setBackground(float positionX, float positionY, float sizeX, float sizeY, const sf::Color& color) {
	background.setPosition(sf::Vector2f(positionX, positionY));
	background.setSize(sf::Vector2f(sizeX, sizeY));
    background.setFillColor(color);
}