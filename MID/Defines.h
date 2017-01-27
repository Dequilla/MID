#pragma once
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <sstream>
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

	inline std::vector<std::string> split(const std::string& input, char delimiter = ' ')
	{
		std::vector<std::string> elements;
		std::stringstream ss;
		ss.str(input);
		std::string item;
		while (std::getline(ss, item, delimiter))
		{
			if (item.empty())
				continue;

			elements.push_back(item);
		}

		return elements;
	}

	inline bool stringToBool(const std::string& str)
	{
		std::string string = str;
		std::transform(string.begin(), string.end(), string.begin(), ::tolower);

		std::istringstream sstring(string);

		bool b;
		sstring >> std::boolalpha >> b;

		return b;
	}

}