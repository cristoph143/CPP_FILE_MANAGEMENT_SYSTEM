#include "../../include/MenuOps/Menu.h"
#include <iostream>
#include <limits>
#include <cstdio>
#include <cstdlib>

namespace MenuOps {

    Menu::Menu() = default;

    void Menu::addMenuItem(const std::string& description, const std::function<void()>& action) {
        items.emplace_back(MenuItem{ description, action });
    }

    void Menu::display() const {
        std::cout << "------------------------------------------------------------\n";
        std::cout << "Menu\n";
        std::cout << "------------------------------------------------------------\n";
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << items[i].description << std::endl;
        }
        std::cout << "0. Exit\n";
        std::cout << "------------------------------------------------------------\n";
        std::cout << "Enter Choice: ";
    }

    int Menu::getValidChoice() const {
        int choice;
        while (!(std::cin >> choice) || choice < 0 || choice > static_cast<int>(items.size())) {
            std::cout << "Invalid choice. Please enter a number between 0 and " << items.size() << ": \n";
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
                std::cout << "Press any key to continue...";
                clearInputBuffer();
                getchar();  // Wait for user confirmation to proceed
            }
        } while (choice != 0);
    }

    void Menu::clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

} // namespace MenuOps
