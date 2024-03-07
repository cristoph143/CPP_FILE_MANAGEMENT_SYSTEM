#ifndef MENUOPS_MENU_H
#define MENUOPS_MENU_H

#include <string>
#include <vector>
#include <functional>

using namespace std;

namespace MenuOps {

    struct MenuItem {
        string description;
        function<void()> action;
    };

    class Menu {
    public:
        Menu();
        void addMenuItem(const string& description, const function<void()>& action);
        void run();

    private:
        vector<MenuItem> items;
        void display() const;
        int getValidChoice() const;
        static void clearInputBuffer();
    };

} // namespace MenuOps

#endif // MENUOPS_MENU_H
