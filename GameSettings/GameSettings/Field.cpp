#include "Field.h"


vector<string> Field::getAvailableValues(const char* str)
{
	vector<string> values;

	pair<multimap<string, string>::iterator, multimap<string, string>::iterator> range = settingsValues.equal_range(str);

	for (auto it = range.first; it != range.second; ++it) {
		values.push_back(it->second);
	}

	return values;
}