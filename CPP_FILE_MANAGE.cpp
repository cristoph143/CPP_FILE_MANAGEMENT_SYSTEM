// CPP_FILE_MANAGE.cpp : Defines the entry point for the application.
//

#include "CPP_FILE_MANAGE.h"

using namespace std;

#include "./include/FileOps/FileOpsUtility.h"
#include "./include/MenuOps/Menu.h"

#include <iostream>
#include <functional>

using namespace MenuOps;
using namespace FileOps;
using namespace std;

class EnhancedMenu : public Menu {
public:
    void initialize() {
        addMenuItem("Create and save file", []() {
            FileOpsUtility::createAndSaveFile();
            });
        addMenuItem("Read file", []() {
            FileOpsUtility::readFiles();
            });
    }
};

int main() {
    EnhancedMenu menu;
    menu.initialize();
    menu.run();
    cout << "Exiting program.\n";
    return 0;
}
