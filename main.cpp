#include "stack.h"
#include "allocator.h"
#include "rec.h"
#include <algorithm>
#include <map>
#include <string>


int main() {
	containers::TStack<TRectangle<int>, my_allocator<TRectangle<int>, 500>> s;
	std::string cmd;
	int index;
	std::cout << "push - to push figure to stack\n"
			  << "insert - to insert figure to stack\n"
			  << "pop - to pop figure from Stack\n"
			  << "erase - to delete figure from Stack\n"
			  << "top - to show first figure\n"
			  << "for_each - to print figures\n"
			  << "map - to show work allocator with map\n"
			  << "exit - to finish execution of program\n";
	while (true) {
		std::cin >> cmd;
		if (cmd == "push") {
			std::cout << "enter coordinates\n";
			TRectangle<int> fig;
			try {
				TRectangle<int> tmp(std::cin);
				fig = tmp;
			} catch(std::exception& err) {
				std::cout << err.what() << std::endl;
				continue;
			}
			s.push(fig);
		} else if (cmd == "insert") {
			std::cout << "enter index\n";
			std::cin >> index;
			auto p = s.begin();
			try {
				s.advance(p, index);
			} catch (std::exception& err) {
				std::cout << err.what() << std::endl;
				continue;
			}
			std::cout << "enter coordinates\n";
			TRectangle<int> fig;
			try {
				TRectangle<int> tmp(std::cin);
				fig = tmp;
			} catch(std::exception& err) {
				std::cout << err.what() << std::endl;
				continue;
			}
			s.insert(p, fig);
		} else if (cmd == "pop") {
			try {
				s.pop();
			} catch(std::exception& err) {
				std::cout << err.what() << std::endl;
				continue;
			}
		} else if (cmd == "erase") {
			std::cout << "enter index\n";
			std::cin >> index;
			auto p = s.begin();
			try {
				s.advance(p, index);
			} catch (std::exception& err) {
				std::cout << err.what() << std::endl;
				continue;
			}
			try {
				s.erase(p);
			} catch (std::exception& err) {
				std::cout << err.what() << std::endl;
				continue;
			}
		
		} else if (cmd == "top") {
			try {
				s.top();
			} catch (std::exception& err) {
				std::cout << err.what() << std::endl;
				continue;
			}
			(s.top()).Print();
		} else if (cmd == "for_each") {
			std::for_each(s.begin(), s.end(), [] (TRectangle<int> tmp) {return tmp.Print();});
		} else if (cmd == "exit") {
			break;
		} else if (cmd == "map"){
			std::map<int, int, std::less<>, my_allocator<std::pair<const int, int>, 1000>> tree;
			for (int i = 0; i < 6; i++) {
				tree[i] = i * i;
			}
			std::for_each(tree.begin(), tree.end(), [](std::pair<int, int> X) {std::cout << X.first << " " << X.second << " ";});
			std::cout << std::endl;
		} else {
			std::cout << "Wrong comand\n";
			continue;
		}

	}
	
}

