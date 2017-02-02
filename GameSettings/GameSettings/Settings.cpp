#include "Settings.h"
#include "StringField.h"
#include "BoolField.h"
#include "IntField.h"
#include "GraphicsQualityField.h"
#include <fstream>
#include "tinystr.h"
#include "tinyxml.h"

using namespace std;



Settings::Settings()
{
	//Set default values
	resolution = new StringField("640*480", "resolution", this);
	fields.push_back(resolution);

	fullScreenMode = new BoolField(true, "full-screen_mode", this);
	fields.push_back(fullScreenMode);

	antialiasing = new StringField("MULTISAMPLE_NONE", "antialiasing", this);
	fields.push_back(antialiasing);

	viewDistance = new IntField(500, "view_distance", 100, 1000, this);
	fields.push_back(viewDistance);

	textureQuality = new StringField("Medium", "texture_quality", this);
	fields.push_back(textureQuality);

	dynamicLightning = new BoolField(false, "dynamic_lighting", this);
	fields.push_back(dynamicLightning);

	shadowsQuality = new StringField("Medium", "shadows_quality", this);
	fields.push_back(shadowsQuality);

	graphicsQuality = new GraphicsQualityField("Normal", "graphics_quality", this);
	fields.push_back(graphicsQuality);
}


Settings::~Settings()
{

	for (auto field : fields) {
		delete field;
	}

}


void Settings::manualChange(const char* field, const char* value)
{
	try {
		//Try get field by name and change value
		Field* currentField = (this->*fieldsLUT.at(field));
		currentField->setValue(value);

		//Check if setting which affects graphics_quality is changed. Set graaphics_quality to Custom if true
		if (find(qualitySettings.begin(), qualitySettings.end(), field) != qualitySettings.end()) {
			
			GraphicsQualityField* graphicsQualityPtr = static_cast<GraphicsQualityField*>(graphicsQuality);
			graphicsQualityPtr->saveCustomField(field, value);

			graphicsQuality->undoValue("Custom");
		}
	}
	catch (const out_of_range& e)
	{
		cout << "Please enter correct settings field!" << endl;
	}

}


void Settings::autoChange(const char* field, const char* value)
{
	try {
		//Try get field by name and change value
		Field* currentField = (this->*fieldsLUT.at(field));
		currentField->undoValue(value);
	}
	catch (const out_of_range& e)
	{
		cout << "Please enter correct settings field!" << endl;
	}

}

void Settings::printField(const char* field)
{
	try {
		//Try get field by name and print value
		Field* currentField = (this->*fieldsLUT.at(field));
		currentField->printValue();
	}
	catch (const out_of_range& e)
	{
		cout << "Please enter correct settings field!" << endl;
	}
}

void Settings::printAllSettings()
{
	for (auto field : fields) {
		field->printValue();
	}

}

void Settings::setOutputFormat(const char* str)
{
	//Check if entered format is available and set
	if (formatsLUT.find(str) != formatsLUT.end()) {
		format = str;
		this->printDoneMessage();
	}
	else
	{
		cout << "Please enter correct format!" << endl;
	}
	
}

void Settings::saveToFile(const char* name)
{

	try
	{
		//Check if correct format is set and try to formate and save file
		(this->*formatsLUT.at(format))(name);

	}
	catch(const out_of_range& e)
	{
		cout << "First need to set format of the file!" << endl;
	}
	
}


void Settings::saveToBin(const char* name) const
{
	//Format file name
	string fileName = string{ name } +string{ "." } +format;

	ofstream file1(fileName, ios::out | ios::binary);
	if (file1.good()) {
		
		//Format output data
		string data;
		for (auto field : fields) {
			data += field->getField() + " " + field->getValue() + ' ';
		}

		//Write data to the file
		file1.write(&data.c_str()[0], data.size());
		file1.close();
		this->printDoneMessage();
	}
	else {
		cout << "File error write" << endl;
	}
	

}

void Settings::saveToXml(const char* name) const
{
	try
	{
		//Format XML data
		TiXmlDocument doc;

		//All pointers must not be deleted. TinyXML will auto delete them
		TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "", "");
		doc.LinkEndChild(decl);
		
		TiXmlElement *root = new TiXmlElement("GameSettings");
		doc.LinkEndChild(root);
	
		for (auto field : fields) {
			TiXmlElement *settingsField = new TiXmlElement(field->getField().c_str());
			root->LinkEndChild(settingsField);
			TiXmlText  *settingsValue = new TiXmlText(field->getValue().c_str());
			settingsField->LinkEndChild(settingsValue);
		}
		

		string fileName = string{ name } + ".xml";
		doc.SaveFile(fileName.c_str());
		this->printDoneMessage();
	}
	catch (...)
	{
		cout << "Write Xml file error!" << endl;
	}

}

void Settings::addFieldInStack(const char* field, const char* value)
{ 
	//Clearing "redo" stack
	if (undoValues.size() > 0) {
		stack<pair<string, string>>().swap(undoValues);
	}
	//Adding "previous" field, value to the stack
	oldValues.push(pair<string, string>{ string{ field }, string{ value } }); 
};


void Settings::undo()
{
	if (oldValues.size() > 0) {

		pair<string, string> oldValue = oldValues.top();
		oldValues.pop();

		//Push undone value to the "redo" stack
		string field = (this->*fieldsLUT.at(oldValue.first))->getField();
		string value = (this->*fieldsLUT.at(oldValue.first))->getValue();
		undoValues.push(pair<string, string>{field , value });

		//Revert value to the previous
		(this->*fieldsLUT.at(oldValue.first))->undoValue(oldValue.second.c_str());

		this->printDoneMessage();
	}
	else {
		cout << "Nothing to Undo!" << endl;
	}


}

void Settings::redo()
{
	if (undoValues.size() > 0) {
		//Get value from the "redo" stack
		pair<string, string> newValue = undoValues.top();
		undoValues.pop();
		
		//Push redone value to the "undo" stack
		string field = (this->*fieldsLUT.at(newValue.first))->getField();
		string value = (this->*fieldsLUT.at(newValue.first))->getValue();
		oldValues.push(pair<string, string>{field, value });
		
		//Cancel undone command
		(this->*fieldsLUT.at(newValue.first))->undoValue(newValue.second.c_str());
		this->printDoneMessage();
	}
	else {
		cout << "Nothing to Redo!" << endl;
	}

}