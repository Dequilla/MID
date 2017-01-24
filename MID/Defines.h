#pragma once
#include <assert.h>
#include <iostream>
#include <string>

#ifdef DEBUG
	#define DEBUG_DEFINED true
#else
	#define DEBUG_DEFINED false
#endif

namespace deq
{

	inline void assertMsg(std::string message)
	{
		std::cout << "Error at assertion: " << message << std::endl;
		assert(!DEBUG_DEFINED);
	}

}