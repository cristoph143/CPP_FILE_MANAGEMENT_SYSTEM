#include "../../include/MenuOps/Menu.h"
#include <chrono>
#include <iostream>
#include <thread>

namespace MenuOps {

    Menu::Menu() {}

    void Menu::addMenuItem(const MenuItem& item) { items.push_back(item); }

    void Menu::display() const {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << items[i].description << std::endl;
        }
        std::cout << "0. Exit" << std::endl;
    }

    void Menu::processChoice(int choice) {
        if (choice > 0 && choice <= static_cast<int>(items.size())) {
            items[choice - 1].action();
            // Sleep after executing the choice to allow user to read any output before
            // continuing
            std::cout << "Action completed. Returning to menu shortly..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    int Menu::getChoice() const {
        int choice;
        while (true) {
            std::cout << "Enter choice: ";
            std::cin >> choice;

            if (std::cin.fail() || choice < 0 || choice > static_cast<int>(items.size())) {
                std::cin.clear(); // Clears the error flag.
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards the rest of the input.
                std::cout << "Invalid input. Please enter a number between 0 and " << items.size() << "." << std::endl;
            }
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears any leftover input.
                break;
            }
        }
        return choice;
    }


    void Menu::run() {
        int choice;
        do {
            clearScreen();
            display();
            choice = getChoice();
            processChoice(choice);
        } while (choice != 0);
    }

    void Menu::clearScreen() {
        int ret = 0;
        #if defined _WIN32
                ret = system("cls");
        #else
                ret = system("clear");
        #endif

        if (ret != 0) {
            std::cerr << "Failed to clear the screen." << std::endl;
        }

        // Sleep for a short interval after clearing the screen
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

} // namespace MenuOps
