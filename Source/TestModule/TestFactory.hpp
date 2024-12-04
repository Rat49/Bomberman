#pragma once
#include "TestBase.hpp"
#include <memory>

class TestFactory
{
public:
	virtual std::shared_ptr<TestBase> createTest() const = 0;
};