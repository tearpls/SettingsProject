#include "InputHandler.h"
#include <iostream>
#include <sstream>



const map<string, void (InputHandler::*)() const> InputHandler::commandsLUT
{
	{ string{ "change" }, &InputHandler::change },
	{ string{ "get" }, &InputHandler::get },
	{ string{ "print" }, &InputHandler::print },
	{ string{ "format" }, &InputHandler::format },
	{ string{ "save" }, &InputHandler::save },
	{ string{ "exit" }, &InputHandler::exit },
	{ string{ "undo" }, &InputHandler::undo },
	{ string{ "redo" }, &InputHandler::redo }

};

InputHandler::InputHandler()
{
	
	currentSettings = new Settings();
}

void InputHandler::getInput(const string& command)
{
	
	//Parsing input string by ' ' delimiter and saving to vector
	stringstream ss(command);
	currentCommand.clear();

	for (string tok; getline(ss, tok, ' '); currentCommand.push_back(tok));

	this->executeCommand();

}

void InputHandler::executeCommand()
{
	try
	{
		(this->*commandsLUT.at( currentCommand.at(0) ))();
	}
	catch (const out_of_range& e)
	{
		cout << "Please enter correct command!" << endl;

	}
}

void InputHandler::change() const 
{ 
	try
	{
		currentSettings->manualChange(currentCommand.at(1).c_str(), currentCommand.at(2).c_str());
	}
	catch (const out_of_range& e)
	{
		cout << "Please enter correct settings field and desired value!" << endl;
	}
};

void InputHandler::get()	const 
{ 
	try
	{
		currentSettings->printField(currentCommand.at(1).c_str());
	}
	catch (const out_of_range& e)
	{
		cout << "Settings field should not be blank!" << endl;
	}
	
};

void InputHandler::print() const 
{ 
	currentSettings->printAllSettings();
};

void InputHandler::format()const 
{ 
	try
	{
		currentSettings->setOutputFormat(currentCommand.at(1).c_str());
	}
	catch (const out_of_range& e)
	{
		cout << "Please enter correct format!" << endl;
	}
};

void InputHandler::save() const 
{ 
	try
	{
		currentSettings->saveToFile(currentCommand.at(1).c_str());
	}
	catch (const out_of_range& e)
	{
		cout << "Please enter correct file name!" << endl;
	}
};

void InputHandler::exit() const 
{ 
	cout << "exit" << endl; 
};

void InputHandler::undo()  const 
{ 
	currentSettings->undo();
};

void InputHandler::redo()  const 
{ 
	currentSettings->redo();
};