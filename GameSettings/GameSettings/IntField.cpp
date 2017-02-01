#include "IntField.h"


void IntField::printValue()
{
	cout << setw(21) << left << field << ": " << value << endl;
}

void IntField::setValue(const char* str)
{
	try
	{
		int val = stoi(str);
		if (val >= min && val <= max) {

			currentSettings->addFieldInStack(field.c_str(), this->getValue().c_str());

			value = val;
		}
		else {
			cout << "Please enter value within allowable range!" << endl;
		}
	}
	catch (...)
	{
		cout << "Please enter correct value for the " << field << " setting!" << endl;
	}

}

void IntField::undoValue(const char* str)
{
	try
	{
		int val = stoi(str);
		if (val >= min && val <= max) {

			value = val;
		}
		else {
			cout << "Please enter value within allowable range!" << endl;
		}
	}
	catch (...)
	{
		cout << "Please enter correct value for the " << field << " setting!" << endl;
	}

}


string IntField::getField()
{
	return field;
}


string IntField::getValue()
{
	return to_string(value);
}