#include "Test.hpp"
#include "Test.Child.hpp"

#include <iostream>

Test::Test()
    : firstborn(nullptr)
{
	std::cout	<< __func__	<< '['	<< __LINE__	<< ']'	<< std::endl;
}

Test::~Test()
{
	std::cout	<< __func__	<< '['	<< __LINE__	<< ']'	<< std::endl;
}