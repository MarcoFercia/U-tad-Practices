#pragma once
#include <sstream>





template <typename T>

std::string stringFromNumber(T val)
{
	std::stringstream cad("");
	cad << val;
	return cad.str();

	
}
