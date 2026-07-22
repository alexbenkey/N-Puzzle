#ifndef TEST_HPP
#define TEST_HPP

class Test
{
#pragma region "Nested Classes"
public:
    class Child;
#pragma endregion
private:
	class Child*	firstborn;

public:
    Test();
    ~Test();
};

#include "Test.Child.hpp"

#endif