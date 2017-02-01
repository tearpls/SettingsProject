#include "GraphicsQualityField.h"


void GraphicsQualityField::printValue()
{
	cout << setw(21) << left << field << ": " << value << endl;
}


void GraphicsQualityField::setValue(const char* str)
{
	//Get all available values
	vector<string> availableValues = getAvailableValues(field.c_str());

	//Check if user entered correct value
	if (find(availableValues.begin(), availableValues.end(), str) != availableValues.end())
	{
		currentSettings->addFieldInStack(field.c_str(), value.c_str());
		value = str;
		
		this->changeSettings();
	}
	else {

		cout << "Please enter correct value for the " << field << "setting!" << endl;
	}

}

void GraphicsQualityField::undoValue(const char* str)
{
	//Get all available values
	vector<string> availableValues = getAvailableValues(field.c_str());

	//Check if user entered correct value
	if (find(availableValues.begin(), availableValues.end(), str) != availableValues.end())
	{
		
		value = str;

		this->changeSettings();
	}
	else {

		cout << "Please enter correct value for the " << field << "setting!" << endl;
	}

}


void GraphicsQualityField::changeSettings()
{
	pair<multimap<string, pair<string, string>>::iterator, multimap<string, pair<string, string>>::iterator> range = graphicsQualityMapping.equal_range(this->value.c_str());

	for (auto it = range.first; it != range.second; ++it) {
		
		string settingsField = it->second.first;
		string settingsValue = it->second.second;

		currentSettings->autoChange(settingsField.c_str(), settingsValue.c_str());
	}

}


string GraphicsQualityField::getField()
{
	return field;
}


string GraphicsQualityField::getValue()
{
	return value;
}


void GraphicsQualityField::saveCustomField(const char* field, const char* value)
{
	pair<multimap<string, pair<string, string>>::iterator, multimap<string, pair<string, string>>::iterator> range = graphicsQualityMapping.equal_range("Custom");

	for (auto it = range.first; it != range.second; ++it) {

		string settingsField = it->second.first;
		string settingsValue = it->second.second;
		if (field == settingsField) {
			it->second.second = value;
		}
	}

}