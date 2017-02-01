// GameSettings.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "Settings.h"
#include "InputHandler.h"

int main()
{
	string command;
	InputHandler* iHandler = new InputHandler();

	cout << "Available commands: change, get, print, format, save, exit, undo, redo " << endl;
	cout << "Important: Commands and values are case sensitive!" << endl;

	while (command != "exit") {
		cout << "Enter command:" << endl;
		getline(cin, command);
		iHandler->getInput(command);

	}
	delete iHandler;

    return 0;
}

