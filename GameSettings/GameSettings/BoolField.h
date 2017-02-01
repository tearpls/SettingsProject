#pragma once
#include "Field.h"
#include "Settings.h"

/*
Class for boolean fields
*/

class BoolField : public Field
{
public:
	BoolField(bool bValue, const char* fieldName, Settings* settings) {
		value = bValue; 
		field = fieldName;
		currentSettings = settings;
	};
	virtual ~BoolField() {};

	virtual void printValue() override;

	virtual void setValue(const char* str) override;
	
	virtual void undoValue(const char* str) override;

	virtual string getField() override;

	virtual string getValue() override;

private:
	bool value;
	string field;
	Settings* currentSettings;
	
	//map for converting string to bool 
	map<string, bool> boolMapping 
	{
		{ string{"true"}, true},
		{ string{"false"}, false }
	};
};

