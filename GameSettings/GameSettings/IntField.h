#pragma once
#include "Field.h"
#include "Settings.h"

/*
Class for int fields
*/

class IntField :
	public Field
{
public:
	IntField(int iValue, const char* fieldName, int min, int max, Settings* settings) : min(min), max(max) { 
		value = iValue; 
		field = fieldName;
		currentSettings = settings;
	};
	~IntField() {};

	virtual void printValue() override;

	virtual void setValue(const char* str) override;

	virtual void undoValue(const char* str) override;

	virtual string getField() override;

	virtual string getValue() override;

private:
	int value;
	string field;
	const int min;
	const int max;
	Settings* currentSettings;
};

