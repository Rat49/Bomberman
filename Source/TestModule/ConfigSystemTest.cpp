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
	configSystem = new ConfigSystem();
}

void ConfigSystemTest::run()
{
	LOG("ConfigSystemTest: run()");

	ConfigFile file1("../../Data/Config/config.ini", true);
	configSystem->addFile(file1);
	std::cout << file1.getSection("Files").getValue("one").getString() << std::endl;
	configSystem->setValue("../../Data/Config/config.ini", "database", "server", "lala");
	std::cout << configSystem->getValue("../../Data/Config/config.ini", "database", "server").getString() << std::endl;;
}

bool ConfigSystemTest::isComplete() const
{
	return true;
}
