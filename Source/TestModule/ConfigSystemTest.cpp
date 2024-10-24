#include "TestModule/ConfigSystemTest.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Logs.hpp"
#include <iostream>

// instead of namespace this could be also defined inside run() method, because it is only used there
namespace {
	const std::string X = "x";
	const std::string Y = "y";
	const std::string WIDTH = "width";
	const std::string HEIGHT = "height";
	const std::string PATH_WALKING_ANIMATION = "../../Data/Config/WalkingAnimation.ini";
}

const std::string& ConfigSystemTest::getName() const
{
	return Name;
}

void ConfigSystemTest::setup()
{
	LOG("ConfigSystemTest: setup()");
}

void ConfigSystemTest::run()
{
	LOG("ConfigSystemTest: run()");

	LOG("Parsing WalkingAnimation file");
	Modules::Config->addFile(PATH_WALKING_ANIMATION);
	const ConfigFile& walkingAnimations = Modules::Config->getFile(PATH_WALKING_ANIMATION);

	const auto& sections = walkingAnimations.getAllSections();

	for(const auto& sectionName : sections)
	{
		if (!walkingAnimations.isSectionPresent(sectionName))
			break;

		if (walkingAnimations.getSection(sectionName).areValuesPresent({X, Y, WIDTH, HEIGHT}))
		{
			//take values for animation
			const ConfigSection& mySection = walkingAnimations.getSection(sectionName);
			float x = mySection.getValue(X).getFloat();
			float y = mySection.getValue(Y).getFloat();
			int32_t width = mySection.getValue(WIDTH).getInt32();
			int32_t height = mySection.getValue(HEIGHT).getInt32();
			LOG("x: $, y: $, width: $, heigth: $", x, y, width, height);
		}
	}
}

bool ConfigSystemTest::isComplete() const
{
	return true;
}
