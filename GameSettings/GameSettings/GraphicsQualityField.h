#pragma once
#include "Field.h"
#include <vector>
#include "Settings.h"

/*
Class for graphics_quality field
*/

class GraphicsQualityField :
	public Field
{
public:
	GraphicsQualityField(const char* str, const char* fieldName, Settings* settings) {
		value = str;
		field = fieldName;
		currentSettings = settings;
	};
	~GraphicsQualityField() {};
	virtual void printValue() override;
	virtual void setValue(const char* str) override;
	
	virtual void undoValue(const char* str) override;

	virtual string getField() override;

	virtual string getValue() override;

	void saveCustomField(const char* field, const char* value);

private:
	string value;
	string field;
	Settings* currentSettings;
	//Changing corresponding settings fields regarding on the quality selected
	void changeSettings();

	//Graphics Quality settings
	multimap<string, pair<string, string> > graphicsQualityMapping
	{
		{ "Low",  pair<string, string>{"texture_quality", "Low"} },
		{ "Low",  pair<string, string>{"dynamic_lighting", "false"} },
		{ "Low",  pair<string, string>{"shadows_quality", "Low"} },

		{ "Normal",  pair<string, string>{"texture_quality", "Medium"} },
		{ "Normal",  pair<string, string>{"dynamic_lighting", "false"} },
		{ "Normal",  pair<string, string>{"shadows_quality", "Medium"} },

		{ "Hight",  pair<string, string>{"texture_quality", "Hight"} },
		{ "Hight",  pair<string, string>{"dynamic_lighting", "true"} },
		{ "Hight",  pair<string, string>{"shadows_quality", "Hight"} },

		{ "Custom",  pair<string, string>{"texture_quality", "Medium"} },
		{ "Custom",  pair<string, string>{"dynamic_lighting", "false"} },
		{ "Custom",  pair<string, string>{"shadows_quality", "Medium"} },

	};

	
	
};
