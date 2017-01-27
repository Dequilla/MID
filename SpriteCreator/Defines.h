#pragma once
#include <Windows.h>

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

	struct File
	{
		bool success = false;
		OPENFILENAME file;
	};

	// Example file type text = "Image file\0*.png\0" (TODO TODO NOWfix by not using std::string)
	inline File openFileDialog(std::string title, std::string filetypes = "Text files\0*.txt\0\0")
	{
		Sleep(1000); // For some reason it doesnt seem to work without this

		char filename[MAX_PATH];
		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = filetypes.c_str();
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = title.c_str();
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON;

		if (GetOpenFileNameA(&ofn))
		{
			std::cout << "Opening file: \"" << filename << "\"\n";
			File file;
			file.success = true;
			file.file = ofn;
			return file;
		}
		else
		{
			switch (CommDlgExtendedError())
			{
			case CDERR_DIALOGFAILURE:	std::cout << "CDERR_DIALOGFAILURE\n";   break;
			case CDERR_FINDRESFAILURE:	std::cout << "CDERR_FINDRESFAILURE\n";  break;
			case CDERR_INITIALIZATION:	std::cout << "CDERR_INITIALIZATION\n";  break;
			case CDERR_LOADRESFAILURE:	std::cout << "CDERR_LOADRESFAILURE\n";  break;
			case CDERR_LOADSTRFAILURE:	std::cout << "CDERR_LOADSTRFAILURE\n";  break;
			case CDERR_LOCKRESFAILURE:	std::cout << "CDERR_LOCKRESFAILURE\n";  break;
			case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
			case CDERR_MEMLOCKFAILURE:	std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
			case CDERR_NOHINSTANCE:		std::cout << "CDERR_NOHINSTANCE\n";     break;
			case CDERR_NOHOOK:			std::cout << "CDERR_NOHOOK\n";          break;
			case CDERR_NOTEMPLATE:		std::cout << "CDERR_NOTEMPLATE\n";      break;
			case CDERR_STRUCTSIZE:		std::cout << "CDERR_STRUCTSIZE\n";      break;
			case FNERR_BUFFERTOOSMALL:	std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
			case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
			case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
			default: std::cout << "File dialog cancelled.\n";
			}

			File file;
			file.success = false;
			return file;
		}
	}
}