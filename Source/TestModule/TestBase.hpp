#pragma once
#include <string>

/* 
* Generic interface for the test.
* Implement your test based on this class.
*/
class TestBase
{
public:
	virtual const std::string& getName() const = 0;
	virtual void setup() = 0;
	virtual void run() = 0;
	virtual void update(float deltaTime) = 0;
	virtual bool isComplete() const = 0;
};