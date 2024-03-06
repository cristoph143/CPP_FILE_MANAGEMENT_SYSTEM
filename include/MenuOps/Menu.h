#ifndef MENUOPS_MENU_H
#define MENUOPS_MENU_H

#include <string>
#include <vector>
#include <functional>

namespace MenuOps {

    struct MenuItem {
        std::string description;
        std::function<void()> action;
    };

    class Menu {
    public:
        Menu();
        void addMenuItem(const std::string& description, const std::function<void()>& action);
        void run();

    private:
        std::vector<MenuItem> items;
        void display() const;
        int getValidChoice() const;
        static void clearInputBuffer();
    };

} // namespace MenuOps

#endif // MENUOPS_MENU_H
