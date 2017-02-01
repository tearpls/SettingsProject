#include "StringField.h"


void StringField::printValue()
{

	cout << setw(21) << left << field << ": " << value << endl;
}

void StringField::setValue(const char* str)
{
		//Get all available values
		vector<string> availableValues = getAvailableValues(field.c_str());
		
		//Check if user entered correct value
		if (find(availableValues.begin(), availableValues.end(), str) != availableValues.end())
		{

			currentSettings->addFieldInStack(field.c_str(), value.c_str());
			
			value = str;
		}
		else {

			cout << "Please enter correct value for the " << field << " setting!" << endl;
		}

}

void StringField::undoValue(const char* str)
{
	//Get all available values
	vector<string> availableValues = getAvailableValues(field.c_str());

	//Check if user entered correct value
	if (find(availableValues.begin(), availableValues.end(), str) != availableValues.end())
	{

		value = str;
	}
	else {

		cout << "Please enter correct value for the " << field << " setting!" << endl;
	}

}


std::string StringField::getField()
{
	return field;
}


std::string StringField::getValue()
{
	return value;
}