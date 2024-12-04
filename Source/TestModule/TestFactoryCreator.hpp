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
	std::shared_ptr<TestBase> createTest() const override
	{
		return std::make_shared<T>();
	}
};