// Place this file under include/MenuOps/Menu.h
#ifndef MENU_H
#define MENU_H

#include <functional>
#include <string>
#include <vector>

namespace MenuOps {

	struct MenuItem {
		std::string description;
		std::function<void()> action;
	};

	class Menu {
	public:
		Menu();
		void addMenuItem(const MenuItem& item);
		void display() const;
		void processChoice(int choice);
		int getChoice() const;
		void run();

	private:
		std::vector<MenuItem> items;
		static void clearScreen();
	};

} // namespace MenuOps

#endif // MENU_H
