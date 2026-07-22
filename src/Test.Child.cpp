#include "Test.Child.hpp"

#include <iostream>

Test::Child::Child(void)
{
	std::cout	<< __func__	<< '['	<< __LINE__	<< ']'	<< std::endl;
}

Test::Child::~Child(void)
{
	std::cout	<< __func__	<< '['	<< __LINE__	<< ']'	<< std::endl;
}