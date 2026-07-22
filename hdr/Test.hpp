#ifndef TEST_HPP
#define TEST_HPP

class Test
{
public:
    class Child;
private:
	class Child*	firstborn;

public:
    Test();
    ~Test();
};

#include "Test.Child.hpp"

#endif