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

	ConfigFile file1("../../Data/Config/config.ini", true);
	Modules::Config->addFile(file1);

	ConfigFile questSystemFile("../../Data/Config/questSystem.ini", true);
	Modules::Config->addFile(questSystemFile);

	std::cout << file1.getSection("Files").getValue("one").getString() << std::endl;
	Modules::Config->setValue("../../Data/Config/config.ini", "database", "server", "lala");
	std::cout << Modules::Config->getValue("../../Data/Config/config.ini", "database", "server").getString() << std::endl;;
}

bool ConfigSystemTest::isComplete() const
{
	return true;
}
