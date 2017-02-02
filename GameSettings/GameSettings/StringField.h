#pragma once
#include "Field.h"
#include <vector>
#include "Settings.h"

/*
Class for string fields
*/

class StringField :
	public Field
{
public:
	StringField(const char* str, const char* fieldName, Settings* settings) {
		value = str; 
		field = fieldName; 
		currentSettings = settings;
	};
	~StringField() {};
	virtual void printValue() override;

	virtual void setValue(const char* str) override;

	virtual void undoValue(const char* str) override;

	virtual string getField() override;

	virtual string getValue() override;

private:
	string value;
	string field;

	Settings* currentSettings;
};

