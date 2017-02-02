#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Settings.h"

/*
Input handler - get and parse user input
*/

class InputHandler
{
public:
	InputHandler();
	~InputHandler() {};

	//Get and parse input from user
	void getInput(const std::string& command);

	//Execute parsed command
	void executeCommand();

private:
	//Available commands
	void change() const;
	void get()	  const;
	void print()  const;
	void format() const;
	void save()   const;
	void exit()   const;
	void undo()   const;
	void redo()   const;

	//Parsed command
	vector<string> currentCommand;

	//Commands Look Up Table 
	const map<string, void (InputHandler::*)() const> commandsLUT
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


	Settings* currentSettings;
};

