#pragma once
#include <string>
#include <map>
#include <vector>
#include "Field.h"
#include <stack>

using namespace std;

/*
Main Settings class for storing and manipulating settings fields
*/
class Settings
{
public:
	Settings();
	~Settings();

	/* Method for changing fields which depends on graphics_quality. */
	void autoChange(const char* field, const char* value);

	/* Method for changing fields by user. Changing grapics_quality to custom if needed */
	void manualChange(const char* field, const char* value);

	void printField(const char* field);

	void printAllSettings();

	void setOutputFormat(const char* format);

	void saveToFile(const char* name);

	/*Add old value of field into stack for 'undo' functional*/
	void addFieldInStack(const char* field, const char* value);

	void undo();

	void redo();
private:
	//Setting fields
	Field* resolution;
	Field* fullScreenMode;
	Field* antialiasing;
	Field* viewDistance; 
	Field* textureQuality; 
	Field* dynamicLightning;
	Field* shadowsQuality;
	Field* graphicsQuality;
	
	vector<Field*> fields;

	//Settings fields which affect graphics_quality field
	vector<string> qualitySettings{ string{ "texture_quality" }, string{ "dynamic_lighting" },  string{ "shadows_quality" } };

	//Fields look-up table
	const map < string, Field* Settings::*  > fieldsLUT
	{
		{ string{ "resolution" }, &Settings::resolution },
		{ string{ "full-screen_mode" }, &Settings::fullScreenMode },
		{ string{ "antialiasing" }, &Settings::antialiasing },
		{ string{ "view_distance" }, &Settings::viewDistance },
		{ string{ "texture_quality" }, &Settings::textureQuality },
		{ string{ "dynamic_lighting" }, &Settings::dynamicLightning },
		{ string{ "shadows_quality" }, &Settings::shadowsQuality },
		{ string{ "graphics_quality" }, &Settings::graphicsQuality }

	};
	
	//Current format
	string format;

	void saveToXml(const char* name) const;

	void saveToBin(const char* name) const;

	//Available formats
	const map < string, void (Settings::*)(const char*) const> formatsLUT
	{
		{ string{ "bin" }, &Settings::saveToBin },
		{ string{ "xml" }, &Settings::saveToXml }
	};
	

	stack< pair<string, string> > oldValues;
	//Undone fields
	stack< pair<string, string> > undoValues;

	void printDoneMessage() const { cout << "Success!" << endl;  };
};

