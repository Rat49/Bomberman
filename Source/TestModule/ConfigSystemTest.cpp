#include "TestModule/ConfigSystemTest.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Logs.hpp"
#include <iostream>

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
	
	LOG("get value from test file -> $", Modules::Config->getValue(FileName::configTest, "Files", "one").getString());
	Modules::Config->setValue(FileName::configTest, "database", "server", "lala");
	LOG("set value lala, and get it from test file -> $", Modules::Config->getValue(FileName::configTest, "database", "server").getString());
	

	// from Lazar Stojanovic's Atlas::parseDescriptionFile
	// first way with getting file
	LOG("Parsing WalkingAnimation file");
	ConfigFile& walkingAnimations = Modules::Config->getFile(FileName::WalkingAnimation);

	int frameIndex = 1;
	const auto& sections = walkingAnimations.getAllSections();
	for(const auto& sectionName : sections)
	{
		if (!walkingAnimations.isSectionPresent(sectionName))
			break;

		if (walkingAnimations.getSection(sectionName).areValuesPresent({"x", "y", "width", "height"}))
		{
			//take values for animation
			const ConfigSection& mySection = walkingAnimations.getSection(sectionName);
			float x = mySection.getValue("x").getFloat();
			float y = mySection.getValue("y").getFloat();
			int32_t width = mySection.getValue("width").getInt32();
			int32_t height = mySection.getValue("height").getInt32();
			LOG("x: $, y: $, width: $, heigth: $", x, y, width, height);
		}
		frameIndex++;
	}
}

bool ConfigSystemTest::isComplete() const
{
	return true;
}
