#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
/*
Abstract class for settings fields
*/
class Field
{
public:
	Field() {};
	virtual ~Field() {};
	
	virtual void setValue(const char* str) = 0;

	virtual void undoValue(const char* str) = 0;

	virtual void printValue() = 0;

	virtual string getField() = 0;

	virtual string getValue() = 0;
protected:

	//Available settings fields values
	multimap<string, string> settingsValues
	{
		{ pair<string, string>{"resolution",  "640*480"} },
		{ pair<string, string>{"resolution", "1024*768"} },
		{ pair<string, string>{"resolution", "1920*1080"} },

		{ pair<string, string>{"antialiasing", "MULTISAMPLE_NONE"} },
		{ pair<string, string>{"antialiasing", "MULTISAMPLE_2"} },
		{ pair<string, string>{"antialiasing", "MULTISAMPLE_4"} },

		{ pair<string, string>{"texture_quality", "Low"} },
		{ pair<string, string>{"texture_quality", "Medium"} },
		{ pair<string, string>{"texture_quality", "Hight"} },

		{ pair<string, string>{"shadows_quality", "Low"} },
		{ pair<string, string>{"shadows_quality", "Medium"} },
		{ pair<string, string>{"shadows_quality", "Hight"} },

		{ pair<string, string>{"graphics_quality", "Low" } },
		{ pair<string, string>{"graphics_quality", "Normal"} },
		{ pair<string, string>{"graphics_quality", "Hight" } },
		{ pair<string, string>{"graphics_quality", "Custom" } }
	};

	//Get corresponding available settings fields values
	vector<string> Field::getAvailableValues(const char* str);

	void printDoneMessage() { cout << "Success!" << endl; };
};


