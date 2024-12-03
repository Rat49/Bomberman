#pragma once
#include <string>
#include <utility>
#include <memory>
#include "TestFactory.hpp"
#include "TestBase.hpp"

template<typename T>
class TestFactoryCreator : public TestFactory
{
public:
	std::pair<std::string, std::shared_ptr<TestBase>> createTest() const override
	{
		std::shared_ptr<TestBase> newTest = std::make_shared<T>();
		return std::make_pair(newTest->getName(), std::move(newTest));
	}
};