#include "../../include/MenuOps/Menu.h"
#include <iostream>
#include <limits>
#include <cstdio>
#include <cstdlib>

using namespace MenuOps;
using namespace std;

namespace MenuOps {

    Menu::Menu() = default;

    void Menu::addMenuItem(const string& description, const function<void()>& action) {
        items.emplace_back(MenuItem{ description, action });
    }

    void Menu::display() const {
        cout << "------------------------------------------------------------\n";
        cout << "Menu\n";
        cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i].description << endl;
        }
        cout << "0. Exit\n";
        cout << "------------------------------------------------------------\n";
        cout << "Enter Choice: ";
    }

    int Menu::getValidChoice() const {
        int choice;
        while (!(cin >> choice) || choice < 0 || choice > static_cast<int>(items.size())) {
            cout << "Invalid choice. Please enter a number between 0 and " << items.size() << ": \n";
            clearInputBuffer();
        }
        return choice;
    }

    void Menu::run() {
        int choice;
        do {
            system("cls || clear");
            display();
            choice = getValidChoice();
            if (choice > 0 && choice <= static_cast<int>(items.size())) {
                items[choice - 1].action();
                cout << "Press any key to continue...";
                clearInputBuffer();
                getchar();  // Wait for user confirmation to proceed
            }
        } while (choice != 0);
    }

    void Menu::clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

} // namespace MenuOps
