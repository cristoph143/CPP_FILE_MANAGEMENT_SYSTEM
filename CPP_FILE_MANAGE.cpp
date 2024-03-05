// CPP_FILE_MANAGE.cpp : Defines the entry point for the application.
//

#include "CPP_FILE_MANAGE.h"

using namespace std;

#include "./include/FileOps/FileOpsUtility.h"
#include "./include/MenuOps/Menu.h"

#include <iostream>

int main() {
	MenuOps::Menu menu;
	FileOps::FileOpsUtility file;

	// Add menu items that are bound to the static methods in FileOpsUtility.
	menu.addMenuItem({ "Create and save file", file.createAndSaveFile });
	menu.addMenuItem({ "Read file", file.readFiles });

	// Run the menu to allow the user to choose options.
	menu.run();

	std::cout << "Exiting...\n";
	return 0;
}
