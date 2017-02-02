#include "BoolField.h"
#include <sstream>


void BoolField::printValue()
{

	cout << setw(21) << left << field << ": " << boolalpha << value << endl;
}

void BoolField::setValue(const char* str)
{
	try
	{

		bool newValue = boolMapping.at(str);

		currentSettings->addFieldInStack(field.c_str(), this->getValue().c_str());
		
		value = newValue;

		this->printDoneMessage();
	}
	catch (...)
	{
		cout << "Please enter correct value for the " << field << " setting!" << endl;
	}

}

void BoolField::undoValue(const char* str)
{
	try
	{
		bool newValue = boolMapping.at(str);
		value = newValue;
	}
	catch (...)
	{
		cout << "Please enter correct value for the " << field << " setting!" << endl;
	}

}



string BoolField::getField()
{
	return field;
}


string BoolField::getValue()
{
	stringstream  ss;
	ss << boolalpha << value;
	return ss.str();
}