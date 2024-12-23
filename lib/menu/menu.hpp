#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_UNCLUDED


#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Menu {
private:
    vector<string> _menu;
public:
    unsigned int dialog() {
        for (string option : _menu) {
            cout << option << endl;
        }
        unsigned int temp = 0;
        do {
            cin >> temp;
        } while (temp >= _menu.size());
        return temp;
    }
    void setMenu(vector<string> menu) {
        _menu = menu;
    }
};


#endif